#ifndef SHOWDATA_H
#define SHOWDATA_H

class MyQLineSeries : public QLineSeries
{
	public:
		MyQLineSeries(){};

	public slots:
		void showPointValue(const QPointF &point, bool state);		
};

class MyQBarSeries : public QBarSeries
{
	public:
		MyQBarSeries(){};

	public slots:
		void showBarValue(bool state);
};

class ShowData : public QWidget
{
	private:
		MyQLineSeries *series;
		QChart *chart;
		QFont font;
		QString plotTitle;
		QBarSet *bSet;
		MyQBarSeries *bSeries;

		std::vector<QBarSet*> barSet;
		std::vector<float> valueVector;
		std::string category, subCategory, day, month, year, stringValue, dataFileName, categoryFileName, detailOfData;
		std::fstream dataFile;
		std::map<std::tuple<QString, QString, int>, float> totalData;	

		std::map<std::pair<QString,int>, float> data;
		QString months[12]={"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
		std::map<QString, int> categoryList;
		std::map<int,int> monthList;	
		std::map<std::string,float> totalValuePerMonth;		
		float value, maxValue, minValue, totalValue;
		int r, g, b;
		bool detailed;

		QColor color[20]={ QColor(47, 79, 79), QColor(178, 34, 34), QColor(147, 112, 219)\
						, QColor(131, 139, 131), QColor(205, 205, 0), QColor(238, 106, 167)\
						, QColor(0, 139, 139), QColor(255, 218, 185), QColor(50, 205, 50)};

	public:
		ShowData();
		~ShowData();
		void loadData();

		QChartView *plot();	
		QChartView *plotLines();	
		float getTotalValue(){ return this-> totalValue; };
		void setCategoryFileName(std::string categoryFileName){ this->categoryFileName = categoryFileName; };
		void setDataFileName(std::string dataFileName){ this->dataFileName = dataFileName; };
		void setPlotTitle(QString plotTitle){ this->plotTitle = plotTitle; };
		void showDetailedData();

};
#endif
