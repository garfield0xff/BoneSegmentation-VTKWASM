#pragma once

class CellPickingInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static CellPickingInteractorStyle* New();

	bool RenderingMode = false;
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	
	vtkNew<vtkParametricSpline> spline;
	vtkNew<vtkKochanekSpline> xSpline;
	vtkNew<vtkKochanekSpline> ySpline;
	vtkNew<vtkKochanekSpline> zSpline;
	

	vtkNew<vtkParametricFunctionSource> functionSource;
	vtkNew<vtkActor> actor;
	vtkNew<vtkPolyData> polyData;
	vtkNew<vtkPolyDataMapper> mapper;
  	


	CellPickingInteractorStyle()
	{
		selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		selectedActor = vtkSmartPointer<vtkActor>::New();
	}

	virtual void OnLeftButtonDown() override
	{
		if (this->RenderingMode)
		{
				vtkNew<vtkNamedColors> colors;
				int* clickPos = this->GetInteractor()->GetEventPosition();
				points->InsertNextPoint(clickPos[0], clickPos[1], 0.0);

				spline->SetXSpline(xSpline);
				spline->SetYSpline(ySpline);
				spline->SetZSpline(zSpline);
				spline->SetPoints(points);
				


				functionSource->SetParametricFunction(spline);

				functionSource->SetUResolution(50 * 4);
				functionSource->SetVResolution(50 * 4);
				functionSource->SetWResolution(50 * 4);
				functionSource->Update();

				
  				mapper->SetInputConnection(functionSource->GetOutputPort());
				
				actor->SetMapper(mapper);
				actor->GetProperty()->SetColor(colors->GetColor3d("DarkSlateGrey").GetData());
				actor->GetProperty()->SetLineWidth(3.0);

				
  				

				this->GetCurrentRenderer()->AddActor(actor);
		}
		

		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}

	virtual void OnKeyPress() override
	{
		vtkRenderWindowInteractor* rwi = this->GetInteractor();
		std::string key = rwi->GetKeySym();

		if(key == "r")
		{
			std::cout << "Rendering Mode execute" << std::endl;
			this->RenderingMode = true;
		}


	}

	vtkSmartPointer<vtkPolyData> Data;
	vtkSmartPointer<vtkDataSetMapper> selectedMapper;
	vtkSmartPointer<vtkActor> selectedActor;
};
