#include "layerdock.h"

#include <QtGlobal>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QInputDialog>
#include <QMessageBox>

LayerDock::LayerDock(Project* project)
{
    setProject(project);

    QPushButton *addLayerBtn = new QPushButton();
    addLayerBtn->setIcon(QIcon::fromTheme("list-add"));
    connect(addLayerBtn, SIGNAL (released()),this, SLOT (addLayer()));

    QPushButton *deleteLayerBtn = new QPushButton();
    deleteLayerBtn->setIcon(QIcon::fromTheme("trash-empty"));
    connect(deleteLayerBtn, SIGNAL (released()),this, SLOT (deleteLayer()));

    QPushButton *toggleVisibleBtn = new QPushButton();
    toggleVisibleBtn->setIcon(QIcon::fromTheme("visibility"));
    connect(toggleVisibleBtn, SIGNAL (released()),this, SLOT (toggleVisibleLayer()));

    QPushButton *renameBtn = new QPushButton();
    renameBtn->setIcon(QIcon::fromTheme("edit-select-text"));
    connect(renameBtn, SIGNAL (released()),this, SLOT (renameLayer()));

    QPushButton *moreBtn = new QPushButton();
    moreBtn->setIcon(QIcon::fromTheme("view-more-horizontal"));
    connect(moreBtn, SIGNAL (released()),this, SLOT (moreLayer()));

    QPushButton *moveUpBtn = new QPushButton();
    moveUpBtn->setIcon(QIcon::fromTheme("go-up"));
    connect(moveUpBtn, SIGNAL (released()),this, SLOT (moveUp()));

    QPushButton *moveDownBtn = new QPushButton();
    moveDownBtn->setIcon(QIcon::fromTheme("go-down"));
    connect(moveDownBtn, SIGNAL (released()),this, SLOT (moveDown()));


    QHBoxLayout *layerTools = new QHBoxLayout();
    layerTools->setAlignment(Qt::AlignRight);
    layerTools->addWidget(addLayerBtn);
    layerTools->addWidget(deleteLayerBtn);
    layerTools->addWidget(toggleVisibleBtn);
    layerTools->addWidget(renameBtn);
    layerTools->addWidget(moreBtn);
    layerTools->addWidget(moveUpBtn);
    layerTools->addWidget(moveDownBtn);

    tree_->setColumnCount(2);
    tree_->setColumnWidth(0, 160);
    tree_->setHeaderLabels(QStringList() << "Название" << "");

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(tree_);
    vbox->addLayout(layerTools);

    QGroupBox *vboxGroup = new QGroupBox();
    vboxGroup->setLayout(vbox);

    this->setMinimumWidth(280);
    this->setMinimumHeight(100);
    this->setWidget(vboxGroup);
}

void LayerDock::addLayer()
{
    Layer* newLayer = new Layer();
    getProject()->pushLayer(newLayer);
    qint64 topLevelIndex = getCurrentTopLevelIndex();
    update();
    QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
    tree_->setCurrentItem(newSelectedLayer);
}

void LayerDock::deleteLayer()
{
    qint64 topLevelIndex = getCurrentTopLevelIndex();
    qint64 secondLevelIndex = getCurrentSecondLevelIndex();
    bool memLayerSelected = isLayerSelected();
    bool memObjectSelected = isObjectSelected();
    if (memLayerSelected)
    {
        getProject()->removeLayer(tree_->currentIndex().row());
    }
    else if (memObjectSelected)
    {
        getProject()->layerAt(tree_->currentIndex().parent().row())->remove(tree_->currentIndex().row());
    }
    update();
    if (memLayerSelected)
    {
        if (tree_->topLevelItemCount() > 0)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex - 1));
            tree_->setCurrentItem(newSelectedLayer);
        }
    }
    else if (memObjectSelected)
    {
        if (tree_->topLevelItem(topLevelIndex)->childCount() > 0)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            QTreeWidgetItem* newSelectedObject = newSelectedLayer->child(qMax((qint64) 0, secondLevelIndex - 1));
            tree_->setCurrentItem(newSelectedObject);
        }
        else
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(topLevelIndex);
            tree_->setCurrentItem(newSelectedLayer);
        }
    }
}

void LayerDock::toggleVisibleLayer()
{
    if (tree_->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().row();
        bool currentVisible = getProject()->layerAt(currentTopLevelIndex)->isVisible();
        getProject()->layerAt(currentTopLevelIndex)->setVisible(!currentVisible);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        bool currentVisible = getProject()->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->isVisible();
        getProject()->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->setVisible(!currentVisible);
    }
    update();
}

void LayerDock::renameLayer()
{
    QString newName = QInputDialog::getText(this,
                                 QString::fromUtf8("Введите название"),
                                 QString::fromUtf8("Новое название:"),
                                 QLineEdit::Normal);
    if (tree_->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().row();
        getProject()->layerAt(currentTopLevelIndex)->setName(newName);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        getProject()->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->setName(newName);
    }
    update();
}

void LayerDock::moreLayer()
{
    if (isLayerSelected())
    {
        QMessageBox::critical(this, tr("Предупреждение"),
                tr("<p>Выбран слой</p>"));
    }
    else if (isObjectSelected())
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        QString report = getProject()->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->report(*getProject()->getMap());
        QMessageBox::information(this, tr("Информация об объекте"),
                                 tr(report.toLocal8Bit().data()));
    }
}

void LayerDock::moveUp()
{
    qint64 topLevelIndex = getCurrentTopLevelIndex();
    qint64 secondLevelIndex = getCurrentSecondLevelIndex();
    bool memLayerSelected = isLayerSelected();
    bool memObjectSelected = isObjectSelected();
    if (tree_->currentIndex().parent().row() == -1)
    {
        getProject()->moveUpLayer(topLevelIndex);
    }
    else
    {
        getProject()->layerAt(topLevelIndex)->moveUp(secondLevelIndex);
    }
    update();
    if (memLayerSelected)
    {
        if (topLevelIndex > 0)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex - 1));
            tree_->setCurrentItem(newSelectedLayer);
        }
        else
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            tree_->setCurrentItem(newSelectedLayer);
        }
    }
    else if (memObjectSelected)
    {
        if (secondLevelIndex > 0)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            QTreeWidgetItem* newSelectedObject = newSelectedLayer->child(qMax((qint64) 0, secondLevelIndex - 1));
            tree_->setCurrentItem(newSelectedObject);
        }
        else
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            QTreeWidgetItem* newSelectedObject = newSelectedLayer->child(qMax((qint64) 0, secondLevelIndex));
            tree_->setCurrentItem(newSelectedObject);
        }
    }
}

void LayerDock::moveDown()
{
    qint64 topLevelIndex = getCurrentTopLevelIndex();
    qint64 secondLevelIndex = getCurrentSecondLevelIndex();
    bool memLayerSelected = isLayerSelected();
    bool memObjectSelected = isObjectSelected();
    if (isLayerSelected())
    {
        getProject()->moveDownLayer(topLevelIndex);
    }
    else
    {
        getProject()->layerAt(topLevelIndex)->moveDown(secondLevelIndex);
    }
    update();
    if (memLayerSelected)
    {
        qint64 numberOfLayer = tree_->topLevelItemCount();
        if (topLevelIndex < numberOfLayer - 1)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex + 1));
            tree_->setCurrentItem(newSelectedLayer);
        }
        else
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            tree_->setCurrentItem(newSelectedLayer);
        }
    }
    else if (memObjectSelected)
    {
        qint64 numberOfObjectOnLayer = tree_->topLevelItem(topLevelIndex)->childCount();
        if (secondLevelIndex < numberOfObjectOnLayer - 1)
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(qMax((qint64) 0, topLevelIndex));
            QTreeWidgetItem* newSelectedObject = newSelectedLayer->child(qMax((qint64) 0, secondLevelIndex + 1));
            tree_->setCurrentItem(newSelectedObject);
        }
        else
        {
            QTreeWidgetItem* newSelectedLayer = tree_->topLevelItem(topLevelIndex);
            QTreeWidgetItem* newSelectedObject = newSelectedLayer->child(secondLevelIndex);
            tree_->setCurrentItem(newSelectedObject);
        }
    }
}

bool LayerDock::isAnySelected()
{
    return tree_->currentIndex().row() != -1;
}

bool LayerDock::isLayerSelected()
{
    return ((isAnySelected()) && (tree_->currentIndex().parent().row() == -1));
}

bool LayerDock::isObjectSelected()
{
    return ((isAnySelected()) && (!isLayerSelected()));
}

qint64 LayerDock::getCurrentTopLevelIndex()
{
    if (isLayerSelected())
    {
        return tree_->currentIndex().row();
    }
    else if (isObjectSelected())
    {
        return tree_->currentIndex().parent().row();
    }
    else
    {
        return -1;
    }
}

qint64 LayerDock::getCurrentSecondLevelIndex()
{
    if (isLayerSelected())
    {
        return -1;
    }
    else if (isObjectSelected())
    {
        return tree_->currentIndex().row();
    }
    else
    {
        return -1;
    }
}

void LayerDock::update()
{
    tree_->clear();
    for (int i = 0; i < getProject()->layerSize(); ++i)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(1);
        item->setText(0, getProject()->layerAt(i)->getName());

        if (getProject()->layerAt(i)->isVisible())
        {
            item->setText(1, "");
        }
        else
        {
            item->setText(1, "Скрыт");
        }
        for (int j = 0; j < getProject()->layerAt(i)->size(); ++j)
        {
            QTreeWidgetItem *subItem = new QTreeWidgetItem(1);
            subItem->setText(0, getProject()->layerAt(i)->at(j)->getName());
            if (getProject()->layerAt(i)->at(j)->isVisible())
            {
                subItem->setText(1, "");
            }
            else
            {
                subItem->setText(1, "Скрыт");
            }
            item->addChild(subItem);
        }
        tree_->addTopLevelItem(item);
        tree_->expandAll();
    }
}

Project* LayerDock::getProject()
{
    return project_;
}

void LayerDock::setProject(Project* value)
{
    project_ = value;
}
