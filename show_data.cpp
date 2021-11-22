#include "includes.hpp"
#include "show_data.h"

ShowData::ShowData()
{ 
	detailed=false;
	font.setBold(true);
	font.setPointSize(10);
	totalValue=0;
}

ShowData::~ShowData() { }

void ShowData::loadData()
{

	dataFile.open(".data/"+dataFileName,std::fstream::in);

	float v=0;
	int m=0;

	while (std::getline(dataFile, category,','))
	{
		std::getline(dataFile, subCategory, ',');
		std::getline(dataFile, stringValue, ',');
		std::getline(dataFile, day, '-');
		std::getline(dataFile, month, '-');
		std::getline(dataFile, year);
		
		std::stringstream vv(stringValue);
		vv >> v;

		std::stringstream mm(month);
		mm >> m;

		std::string c=category;		

		totalData[std::make_tuple(QString::fromStdString(category),QString::fromStdString(subCategory),m)] += v;
		data[std::make_pair(QString::fromStdString(c), m)] += v;

		categoryList[QString::fromStdString(c)]+=1;
		monthList[m]+=1;
	}
}

void MyQLineSeries::showPointValue(const QPointF &point, bool state){ 
	this->setPointLabelsFormat("R$ @yPoint");
	this->setPointLabelsFont(QFont("Times", 12, QFont::Bold));
	this->setPointLabelsVisible(state);
}


void MyQBarSeries::showBarValue(bool state){
	this->setLabelsVisible(state);
	this->setLabelsFormat("R$ @value");
	this->setLabelsAngle(-90);
	this->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
}

void ShowData::showDetailedData(){ detailed=true; }

QChartView *ShowData::plot()
{
	loadData();

	chart = new QChart();

	QValueAxis *axisY = new QValueAxis;
	axisY->applyNiceNumbers();
	axisY->setLabelFormat("%.2f");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);

	for(auto [m,i]:monthList) axisX->append(months[m-1]);

	int k=0;
	for (auto [c,i]:categoryList){
		bSet = new QBarSet(c);
		bSeries = new MyQBarSeries;

		for (auto [m,j]:monthList) bSet->append(data[std::make_pair(c,m)]);

		bSet->setColor(color[k]);
		bSet->setLabelColor(color[k]);
		bSet->setLabelFont(QFont("Times", 12, QFont::Bold));
		bSeries->append(bSet);	

		chart->addSeries(bSeries);
		bSeries->attachAxis(axisX);
		bSeries->attachAxis(axisY);

		QObject::connect(bSeries, &QAbstractBarSeries::hovered,bSeries,&MyQBarSeries::showBarValue);
		k++;
	}

	for (const auto [k,v]:data) valueVector.push_back(v); 

	maxValue=*max_element(valueVector.begin(), valueVector.end());
	minValue=*min_element(valueVector.begin(), valueVector.end());
	chart->setTitle(plotTitle);
	chart->setAnimationOptions(QChart::SeriesAnimations);

	minValue<0? axisY->setRange(int(1.2*minValue/50 - 1)*50, int(1 + 1.2*maxValue/50)*50):axisY->setRange(0,int(1 + 1.2*maxValue/50)*50);

	chart->legend()->setColor(QColor(100,50,200));	
	chart->legend()->setFont(font);
	chart->setLocalizeNumbers(true);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	return chartView;
}

QChartView *ShowData::plotLines()
{
	loadData();

	chart = new QChart();

	QValueAxis *axisY = new QValueAxis;
	axisY->applyNiceNumbers();
	axisY->setLabelFormat("%.2f");

	QCategoryAxis *axisX = new QCategoryAxis;
	axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
	axisX->setStartValue(0);

    chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);

	int k=0;
	for (auto [c,j]:categoryList){
		QPen pen(color[k]);
		pen.setWidth(2);
		series = new MyQLineSeries();	
		series->setPointLabelsColor(color[k]);
		series->setName(c);
		series->setPen(pen); 	
			
		for (auto [m,i]:monthList) series->append(m,data[std::make_pair(c,m)]); 
		
		chart->addSeries(series);
		series->attachAxis(axisX);
		series->attachAxis(axisY);

		series->setPointsVisible(true);
		QObject::connect(series, &QXYSeries::hovered,series,&MyQLineSeries::showPointValue);
		k++;
	}

	for (auto [m,j]:monthList) axisX->append(months[m], m);

	for (const auto [k,v]:data) valueVector.push_back(v); 

	maxValue=*max_element(valueVector.begin(), valueVector.end());
	minValue=*min_element(valueVector.begin(), valueVector.end());
	chart->setTitle(plotTitle);
	chart->setAnimationOptions(QChart::SeriesAnimations);

	minValue<0? axisY->setRange(int(1.2*minValue/50 - 1)*50, int(1 + 1.2*maxValue/50)*50):axisY->setRange(0,int(1 + 1.2*maxValue/50)*50);

	chart->legend()->setColor(QColor(100,50,200));	
	chart->legend()->setFont(font);
	chart->setLocalizeNumbers(true);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	return chartView;
}
