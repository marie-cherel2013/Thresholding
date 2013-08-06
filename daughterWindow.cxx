//Header File
#include "daughterWindow.h"

using namespace std; 

//**********Constructor**********//
daughterWindow::daughterWindow() : Ui_MotherWindow()
{	
	setupUi(this);

	//Memory allocation  
	m_outputWriter = WriterType::New(); 

	//Default Directories
	m_dataDirectory="/work/mcherel/Exercices/GUI/data";
	m_outputTempDirectory="/work/mcherel/Exercices/GUI/bin/outputTemp.png";

	//Connections
	connect(inputButton, SIGNAL(clicked()), this, SLOT(selectInputImage()));
	connect(threshold, SIGNAL(valueChanged(int)), this, SLOT(enterThresholdValue(int)));
	connect(runButton, SIGNAL(clicked()), this, SLOT(run()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveOutput()));
}


//**********Destructor***********//
daughterWindow::~daughterWindow(){}


//**********Slot**********//
void daughterWindow::selectInputImage()
{
	//File selection
	m_inputFileWay = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", m_dataDirectory,"Images (*.png *.gif *.jpg *.jpeg)");

	//Display
	QVTKWidget *inputWidget = new QVTKWidget(this->inputArea);
	display(m_inputFileWay, inputWidget);
}

void daughterWindow::enterThresholdValue(int thresholdValue)
{
	m_threshold=thresholdValue;
}

void daughterWindow::run()
{ 
	//Input Image// 
	ReaderType::Pointer reader = ReaderType::New(); 
	reader->SetFileName(m_inputFileWay.toStdString()); 

	//Threshold Filtering//
	FilterType::Pointer thresholdFilter=FilterType::New(); 
	thresholdFilter->SetInput(reader->GetOutput());
	thresholdFilter->SetLowerThreshold(m_threshold);
	thresholdFilter->SetUpperThreshold(255);
	thresholdFilter->SetOutsideValue(0); 
	thresholdFilter->SetInsideValue(255); 
	
	//Output Image
	m_outputWriter->SetInput(thresholdFilter->GetOutput()); 
	m_outputWriter->SetFileName(m_outputTempDirectory.toStdString());
	m_outputWriter->Update();

	//ITK to VTK
	/*typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer connector=ConnectorType::New();
	connector->SetInput(thresholdFilter->GetOutput());
	connector->Update();*/

	//Display
   QVTKWidget *outputWidget = new QVTKWidget(this->outputArea);
	display("outputTemp.png", outputWidget);
}

void daughterWindow::saveOutput()
{
	// File Way Selection
	m_outputFileWay = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", m_dataDirectory, "Images (*.png *.gif *.jpg *.jpeg)");		

	// Output Saving 
	m_outputWriter->SetFileName(m_outputFileWay.toStdString());
	m_outputWriter->Update();
}


//**********Other Functions**********//
void daughterWindow::display(QString file, QVTKWidget* widget)
{
	//Widget
	widget->resize(221, 257);

	//PNG Reader
	vtkSmartPointer<vtkPNGReader> pngReader = vtkSmartPointer<vtkPNGReader>::New();
	pngReader->SetFileName((file.toStdString()).c_str());

	//Viewer	
	vtkSmartPointer<vtkImageViewer> viewer = vtkSmartPointer<vtkImageViewer>::New();
	viewer->SetInputConnection(pngReader->GetOutputPort());
	viewer->SetColorLevel(128);
	viewer->SetColorWindow(256);

	//Render window	
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow=viewer->GetRenderWindow();

	//Display
	widget->SetRenderWindow(renderWindow);
	renderWindow->Render();
	widget->show();
}

