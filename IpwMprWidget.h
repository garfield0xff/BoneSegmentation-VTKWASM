#pragma once


class IpwMprWidget : public vtkImagePlaneWidget
{
public:
	static IpwMprWidget* New();
	vtkTypeMacro(IpwMprWidget, vtkImagePlaneWidget);

	int sliceIndex[3] = { 0, 0, 0 };

private:
	vtkSmartPointer<vtkImagePlaneWidget> ipw_Widget;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkImageData> imageData;
	vtkSmartPointer<vtkAlgorithmOutput> outputPort;
	vtkSmartPointer<vtkPolyData> polyData;
	vtkSmartPointer<vtkProperty> ipwProp;

	vtkSmartPointer<vtkCellPicker> picker;

	vtkNew<vtkTextProperty> sliceTextProp;
	vtkNew<vtkTextMapper> sliceTextMapper;
	vtkNew<vtkActor2D> sliceTextActor;

	double color[3] = { 0, 0,0 };
	double viewUp[3][3] = { { 0, 0, -1 }, { 0, 0, 1 }, { 0, 1, 0 } };
	double camPos[3] = { 0, 0, 0 };

	int imageDims[3];

	int axis;
	int currentSlice;
	int maxSlice;

public:

	IpwMprWidget()
	{
		this->ipw_Widget = vtkSmartPointer<vtkImagePlaneWidget>::New();
		this->ipwProp = vtkSmartPointer<vtkProperty>::New();
		this->picker = vtkSmartPointer<vtkCellPicker>::New();
	};

	void SetImageData(vtkSmartPointer<vtkImageData> imageData)
	{
		this->imageData = imageData;
	}

	void SetPolyData(vtkSmartPointer<vtkPolyData> polyData)
	{
		this->polyData = polyData;
	}

	void nextSlice()
	{
		if (currentSlice == maxSlice) currentSlice = 0;
		this->sliceIndex[this->axis] += 1;
		this->currentSlice = this->sliceIndex[this->axis];
		cout << "current slice is : " << currentSlice << endl;
		this->ipw_Widget->SetSliceIndex(currentSlice);
	}

	void preSlice()
	{
		if (currentSlice == 0) currentSlice = this->maxSlice;
		this->sliceIndex[this->axis] -= 1;
		this->currentSlice = this->sliceIndex[this->axis];
		cout << "current slice is : " << currentSlice << endl;
		this->ipw_Widget->SetSliceIndex(currentSlice);
	}

	// int* getDimensions()
	// {
	//     int* imageDims;
	//     this->imageData->GetDimensions(imageDims);
	//     return imageDims;
	// }


	void SetText()
	{
		std::string msg = StatusMessage::Format(this->GetSliceIndex(), this->GetMaxSlice(), this->axis);

		sliceTextProp->SetFontSize(20);
		sliceTextProp->SetVerticalJustificationToBottom();
		sliceTextProp->SetJustificationToLeft();

		sliceTextMapper->SetInput(msg.c_str());
		sliceTextMapper->SetTextProperty(sliceTextProp);

		sliceTextActor->SetMapper(sliceTextMapper);
		sliceTextActor->SetPosition(15, 10);

		this->GetDefaultRenderer()->AddActor2D(sliceTextActor);

	}


	void ViewDicom(int axis)
	{

		// this->picker->SetTolerance(0.005);
		this->imageData->GetDimensions(this->imageDims);
		this->axis = axis;
		this->maxSlice = this->imageDims[this->axis];
		// ipw_Widget->SetInteractor(this->renderWindowInteractor);


		// this->color[axis] = 1;
		// this->GetPlaneProperty()->SetColor(color);

		this->SetPicker(this->picker);
		this->SetInputData(this->imageData);
		this->SetPlaneOrientation(this->axis);
		this->SetResliceInterpolateToLinear();
		this->SetTexturePlaneProperty(this->ipwProp);
		this->SetSliceIndex(this->sliceIndex[axis]);
		this->DisplayTextOn();

		this->SetWindowLevel(600, 0);
		this->On();
		this->InteractionOn();

		this->GetDefaultRenderer()->GetActiveCamera()->SetFocalPoint(0, 0, 0);
		this->GetDefaultRenderer()->SetBackground(0, 0, 0);

		this->camPos[axis] = 1;

		this->GetDefaultRenderer()->GetActiveCamera()->SetPosition(this->camPos);
		this->GetDefaultRenderer()->GetActiveCamera()->ParallelProjectionOn();
		this->GetDefaultRenderer()->GetActiveCamera()->SetViewUp(this->viewUp[axis][0], this->viewUp[axis][1], this->viewUp[axis][2]);
		this->GetDefaultRenderer()->ResetCamera();

	}

	int GetMaxSlice() { return this->imageDims[this->axis]; }
	int GetAxis() { return this->axis; }

	vtkSmartPointer<vtkTextMapper> GetTextMapper() { return this->sliceTextMapper; }
	vtkSmartPointer<vtkImageData> GetImageData() { return this->imageData; }
	vtkSmartPointer<vtkCellPicker> GetCellPicker() { return this->picker; }
};