#include "layerdock.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QInputDialog>

LayerDock::LayerDock(Project* project)
{
    project_ = project;

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
    project_->pushLayer(newLayer);
    updateContent();
}

void LayerDock::deleteLayer()
{
    if (isLayerSelected())
    {
        project_->removeLayer(tree_->currentIndex().row());
    }
    else
    {
        project_->layerAt(tree_->currentIndex().parent().row())->remove(tree_->currentIndex().row());
    }
    updateContent();
}

void LayerDock::toggleVisibleLayer()
{
    if (tree_->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().row();
        bool currentVisible = project_->layerAt(currentTopLevelIndex)->isVisible();
        project_->layerAt(currentTopLevelIndex)->setVisible(!currentVisible);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        bool currentVisible = project_->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->isVisible();
        project_->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->setVisible(!currentVisible);
    }
    updateContent();
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
        project_->layerAt(currentTopLevelIndex)->setName(newName);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        project_->layerAt(currentTopLevelIndex)->at(currentSecondLevelIndex)->setName(newName);
    }
    updateContent();
}

void LayerDock::moreLayer()
{
    if (isLayerSelected())
    {

    }
    else if (isObjectSelected())
    {

    }
}

void LayerDock::moveUp()
{
    if (tree_->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().row();
        project_->moveUpLayer(currentTopLevelIndex);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        project_->layerAt(currentTopLevelIndex)->moveUp(currentSecondLevelIndex);
    }
    updateContent();
}

void LayerDock::moveDown()
{
    if (tree_->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().row();
        project_->moveDownLayer(currentTopLevelIndex);
    }
    else
    {
        qint64 currentTopLevelIndex = tree_->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree_->currentIndex().row();
        project_->layerAt(currentTopLevelIndex)->moveDown(currentSecondLevelIndex);
    }
    updateContent();
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

void LayerDock::updateContent()
{

    tree_->clear();
    for (int i = 0; i < project_->layerSize(); ++i)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(1);
        item->setText(0, project_->layerAt(i)->getName());

        if (project_->layerAt(i)->isVisible())
        {
            item->setText(1, "");
        }
        else
        {
            item->setText(1, "Скрыт");
        }
        for (int j = 0; j < project_->layerAt(i)->size(); ++j)
        {
            QTreeWidgetItem *subItem = new QTreeWidgetItem(1);
            subItem->setText(0, project_->layerAt(i)->at(j)->getName());
            if (project_->layerAt(i)->at(j)->isVisible())
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
