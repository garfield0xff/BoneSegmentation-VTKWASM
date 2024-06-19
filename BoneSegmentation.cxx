// #define _EANBLE_WASM_

// #ifdef  _EANBLE_WASM_
// 	#include <emscripten.h>
// 	#include <emscripten/fetch.h>
// #endif 

#include <vtkDICOMImageReader.h>

#include <vtksys/SystemTools.hxx>
#include <vtkImageData.h>
#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkImageReslice.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkInformation.h>
#include <vtkResliceCursorWidget.h>
#include <vtkResliceCursorLineRepresentation.h>
#include <vtkResliceCursor.h>
#include <vtkResliceCursorActor.h>
#include <vtkResliceCursorPolyDataAlgorithm.h>

#include <vtkImageViewer2.h>
#include <vtkResliceImageViewer.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkImagePlaneWidget.h>
#include <vtkCellPicker.h>
#include <vtkObject.h>


#include <vtkRegularPolygonSource.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkAlgorithmOutput.h>
#include <vtkCamera.h>
#include <vtkKochanekSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricSpline.h>

#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkCamera.h>
#include <vtkFlyingEdges3D.h>
#include <vtkMarchingCubes.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkAlgorithmOutput.h>

#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkExtractSelection.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkCommand.h>
#include <sstream>

#include "RscMprWidget.h"
#include "StatusMessage.h"
#include "IpwMprWidget.h"
#include "ImageViewerInteractorStyle.h"
#include "MprImageViewer.h"
#include "MeshRenderer.h"
#include "CellPickingInteractorStyle.h"
#include "testInteractor.h"
#include "vtkResliceCursorCallback.h"

bool isCellPickingMode = false;
bool is2x2Window = false;

int SegmentationStater();

int SegmentationStater() {
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkDICOMImageReader> reader;
	reader->SetDirectoryName("/Users/kimgyujin/Downloads/choi/");
	reader->Update();

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	vtkNew<vtkRenderWindow> renderWindow;
	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

	renderWindowInteractor->SetRenderWindow(renderWindow);
	
	renderWindow->SetMultiSamples(0);
	renderWindow->AddRenderer(renderer);

	MeshRenderer _MeshRenderer;
	_MeshRenderer.setImageData(reader->GetOutput());
	_MeshRenderer.setRenderer(renderer);
	_MeshRenderer.setMeshRenderer();

	vtkNew<CellPickingInteractorStyle> _CellpickingInteractorStyle;

	renderWindowInteractor->SetInteractorStyle(_CellpickingInteractorStyle);
	renderer->SetBackground(colors->GetColor3d("PaleTurquoise").GetData());
	_CellpickingInteractorStyle->SetDefaultRenderer(renderer);

	
	
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

int main()
{
	SegmentationStater();
	return 0;
}
