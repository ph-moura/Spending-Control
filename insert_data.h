#ifndef DESPESAS_H
#define DESPESAS_H

class InsertData : public QWidget 
{
	private:
		float value;
		std::map <std::string, int> mapCategory;
		std::fstream dataFile, categoriesFile, subCategoriesFile;
		std::string category, subCategory, date, categoryFileName, dataFileName, str, type;
		QComboBox *categoryComboBox, *subCategoryComboBox;
		QLineEdit *lineEditValue, *lineEditCategory, *lineEditSubCategory;
		QDateEdit *dateEditDate;
		QStringList listCategories, listSubCategories;
		QFormLayout *formLayout; 
		QPushButton *ok, *cancel;
		void load();

	public:
		InsertData(QWidget*);
		~InsertData();
		void setCategoryFileName(std::string categoryFileName){ this->categoryFileName = categoryFileName;};
		void setDataFileName(std::string dataFileName){ this->dataFileName = dataFileName;};
		void insertCategory();
		void editCategory();
		void dataInput();

	private slots:
		void getText();
		void writeData(std::string category, std::string subCategory, float value, std::string date);
		void close();
		void loadSubCategories();
		void setCategory();
};

#endif
