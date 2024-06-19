#pragma once 

class MeshRenderer
{
public:
	static MeshRenderer* New();

protected:
	vtkSmartPointer<vtkFlyingEdges3D> iso;
	vtkSmartPointer<vtkImageData> imageData;

	vtkSmartPointer<vtkPolyDataMapper> isoMapper;
	vtkSmartPointer<vtkActor> isoActor;

	vtkSmartPointer<vtkOutlineFilter> outline;
	vtkSmartPointer<vtkPolyDataMapper> outlineMapper;
	vtkSmartPointer<vtkActor> outlineActor;

	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkAlgorithmOutput> outputPort;

public:
	MeshRenderer()
	{
		this->iso = vtkSmartPointer<vtkFlyingEdges3D>::New();
		this->isoMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		this->isoActor = vtkSmartPointer<vtkActor>::New();

		this->outline = vtkSmartPointer<vtkOutlineFilter>::New();
		this->outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		this->outlineActor = vtkSmartPointer<vtkActor>::New();
	}

	void setImageData(vtkSmartPointer<vtkImageData> imageData)
	{
		this->imageData = imageData;
	}

	void setRenderer(vtkSmartPointer<vtkRenderer> renderer)
	{
		this->renderer = renderer;
	}

	void setMeshRenderer()
	{
		this->iso->SetInputData(this->imageData);
		this->iso->ComputeGradientsOn();
		this->iso->ComputeNormalsOff();
		this->iso->SetValue(0, 350);

		this->isoMapper->SetInputConnection(this->iso->GetOutputPort());
		this->isoMapper->ScalarVisibilityOff();
		this->isoActor->SetMapper(this->isoMapper);

		this->outline->SetInputData(this->imageData);
		this->outlineMapper->SetInputConnection(this->outline->GetOutputPort());
		this->outlineActor->SetMapper(this->outlineMapper);

		this->renderer->AddActor(this->outlineActor);
		this->renderer->AddActor(this->isoActor);
		this->renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
		this->renderer->GetActiveCamera()->SetPosition(0, -1, 0);
		this->renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
		this->renderer->GetActiveCamera()->Dolly(1.5);
		this->renderer->ResetCamera();
		this->renderer->ResetCameraClippingRange();

	}
	vtkSmartPointer<vtkFlyingEdges3D> getFlyingEdges3D() { return this->iso; }
	vtkSmartPointer<vtkPolyDataMapper> getPolyDataMapper() { return this->isoMapper; }
};