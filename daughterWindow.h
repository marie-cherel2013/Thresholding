#ifndef DEF_daughterWindow
#define DEF_daughterWindow

//General Libraries
#include <string.h>

//Qt Libraries
#include <QFileDialog>
#include <QMainWindow>
#include <QWidget>
#include "QVTKWidget.h"
#include "ui_MotherWindow.h"

//ITK Libraries
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include <itkImageFileWriter.h>

//ITK to VTK Libraries
/* #include <itkImageToVTKImageFilter.h> */

//VTK Libraries
#include <vtkSmartPointer.h> 
#include <vtkImageViewer.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkRenderWindow.h>


class daughterWindow :public QMainWindow, public Ui_MotherWindow
{
	Q_OBJECT // Enable slots and signals 

	public:
   //Image Type//
   typedef itk::Image<unsigned char, 2> ImageType;
   typedef itk::ImageFileReader<ImageType> ReaderType;
   typedef itk::ImageFileWriter<ImageType> WriterType;
   typedef itk::BinaryThresholdImageFilter <ImageType, ImageType> FilterType;

	daughterWindow();	//Constructor
	~daughterWindow();	//Destructor
	void display(QString file, QVTKWidget* widget);

	public slots:
	void selectInputImage();
	void enterThresholdValue(int threshold);
	void run ();
	void saveOutput();
	
	private:
	//Input
	QString m_dataDirectory;
	QString m_inputFileWay;
	
	//Output
	QString m_outputTempDirectory;
	QString m_outputFileWay;
	WriterType::Pointer m_outputWriter;

	//Filter
	int m_threshold;
}; 

#endif 
