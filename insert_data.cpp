#include "includes.hpp"
#include "insert_data.h"

InsertData::InsertData (QWidget *parent) : QWidget(parent) { }

void InsertData::dataInput()
{
	categoryComboBox = new QComboBox(this);
	subCategoryComboBox = new QComboBox(this);

	load();
	loadSubCategories();

	lineEditValue = new QLineEdit(this); 
	dateEditDate = new QDateEdit(QDate::currentDate());
	dateEditDate->setDisplayFormat("d-MM-yyyy");
	dateEditDate->setCalendarPopup(true);	

	formLayout = new QFormLayout();
	formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
	
	formLayout->addRow("&Categoria:", categoryComboBox);
	formLayout->addRow("&Descrição:", subCategoryComboBox);
	formLayout->addRow("&Valor (R$):", lineEditValue);
	formLayout->addRow("D&ata:", dateEditDate);

	ok = new QPushButton("Ok", this);
	ok->setGeometry(10,150, 140,30);

	cancel = new QPushButton("Cancel", this);
	cancel->setGeometry(160,150, 140,30);

	QObject::connect(categoryComboBox, &QComboBox::currentTextChanged, this, &InsertData::loadSubCategories);
	QObject::connect(ok, &QPushButton::clicked, this, &InsertData::getText);
	QObject::connect(cancel, &QPushButton::clicked, this, &InsertData::close);
	
	this->setLayout(formLayout);
	// this->setStyleSheet("border-width: 2px; border-radius: 5px; padding: 4px;");
	setFixedSize(310,200);
	this->setObjectName("dataInput");
	this->show();
}

InsertData::~InsertData(){ }

void InsertData::insertCategory()
{
	categoryComboBox = new QComboBox(this);
	lineEditCategory = new QLineEdit(this); 
	lineEditSubCategory = new QLineEdit(this); 

	setCategoryFileName("main.txt");
	load();	

	formLayout = new QFormLayout();
	formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
	
	formLayout->addRow("&Tipo:", categoryComboBox);
	formLayout->addRow("&Categoria:", lineEditCategory);
	formLayout->addRow("&Descrição:", lineEditSubCategory);

	ok = new QPushButton("Ok", this);
	ok->setGeometry(10,150, 140,30);

	cancel = new QPushButton("Cancel", this);
	cancel->setGeometry(160,150, 140,30);

	QObject::connect(ok, &QPushButton::clicked, this, &InsertData::setCategory);
	QObject::connect(cancel, &QPushButton::clicked, this, &InsertData::close);
	
	this->setLayout(formLayout);
	setFixedSize(310,200);
	this->show();
}

void InsertData::setCategory()
{	
	type=categoryComboBox->currentText().toStdString();
	category = lineEditCategory->text().toStdString();
	subCategory = lineEditSubCategory->text().toStdString();

	categoriesFile.open(".categorias/"+type+".txt", std::fstream::in|std::fstream::app);
	while(std::getline(categoriesFile,str)){
		mapCategory[str] +=1;
	}

	categoriesFile.close();

	if (mapCategory[category]==0){
		categoriesFile.open(".categorias/"+type+".txt",std::fstream::app);
		categoriesFile << category << std::endl;
		categoriesFile.close();
	}

	subCategoriesFile.open(".categorias/"+category+".txt", std::fstream::app);
	subCategoriesFile << subCategory << std::endl;;
	subCategoriesFile.close();
	lineEditSubCategory->clear();
}

void InsertData::load()
{
	categoriesFile.open(".categorias/"+categoryFileName, std::fstream::in|std::fstream::out|std::fstream::app);
	std::string str;	
	while (getline(categoriesFile, str)){
		listCategories << QString::fromStdString(str);
	}
	categoryComboBox->addItems(listCategories);
	categoriesFile.close();
}

void InsertData::getText()
{
	category=categoryComboBox->currentText().toStdString();	
	subCategory=subCategoryComboBox->currentText().toStdString();

	date=dateEditDate->text().toStdString();
	value=lineEditValue->text().toFloat();

	subCategoryComboBox->clear();
	lineEditValue->clear();
	
	writeData(category, subCategory, value, date);
	loadSubCategories();
}

void InsertData::writeData(std::string category, std::string subCategory, float value, std::string date)
{
	dataFile.open(".data/"+dataFileName, std::fstream::in|std::fstream::out|std::fstream::app);
	dataFile << category << "," << subCategory << "," << value << "," << date << std::endl;
	dataFile.close();
}

void InsertData::close()
{
	dataFile.close();
	delete this;
}

void InsertData::loadSubCategories()
{
	std::string str="\0";
	listSubCategories.clear();
	category=categoryComboBox->currentText().toStdString();	
	subCategoriesFile.open((".categorias/"+category+".txt").c_str(), std::fstream::in|std::fstream::out|std::fstream::app);

	while(getline(subCategoriesFile, str)){ listSubCategories.append(QString::fromStdString(str));	}

	subCategoriesFile.close();
	subCategoryComboBox->clear();
	subCategoryComboBox->addItems(listSubCategories);
}
