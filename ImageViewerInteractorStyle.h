#pragma once

class ImageViewerInteractorStyle : public vtkInteractorStyleImage
{
public:
	static ImageViewerInteractorStyle* New();
	vtkTypeMacro(ImageViewerInteractorStyle, vtkInteractorStyleImage);

protected:
	vtkImageViewer2* _ImageViewer;
	IpwMprWidget* _PlaneWidget;
	vtkTextMapper* _StatusMapper;
	vtkCellPicker* _CellPicker;
	vtkNew<vtkInformation> _Information;

	bool isImageViewer = false;
	double* worldPosition;

	int  _Axis;
	int _Slice;
	int _MinSlice;
	int _MaxSlice;

public:
	void SetImageViewer(vtkImageViewer2* imageViewer)
	{
		this->isImageViewer = true;

		_ImageViewer = imageViewer;
		_MaxSlice = imageViewer->GetSliceMax();
		_MinSlice = imageViewer->GetSliceMin();
		_Slice = _MinSlice;
		cout << imageViewer->GetObjectName() << "  Slice Min is : " << _MinSlice << ", Max is : " << _MaxSlice << endl;

	}

	void SetPlaneWidget(IpwMprWidget* planeWidget)
	{
		this->isImageViewer = false;
		_PlaneWidget = planeWidget;
		_CellPicker = planeWidget->GetCellPicker();
		_MaxSlice = planeWidget->GetMaxSlice();
		_Axis = planeWidget->GetPlaneOrientation();
		_Slice = 0;
	}

	void SetStatusMapper(vtkTextMapper* statusMapper)
	{
		_StatusMapper = statusMapper;
	}


protected:

	void MoveSliceForward()
	{
		if (_Slice < _MaxSlice)
		{
			_Slice += 1;

			cout << "MoveSliceForward : " << _Slice << endl;

			if (this->isImageViewer) {
				_ImageViewer->SetSlice(_Slice);
				std::string msg = StatusMessage::Format(_Slice, _MaxSlice, _ImageViewer->GetSliceOrientation());
				_StatusMapper->SetInput(msg.c_str());
				_ImageViewer->Render();
			}
			else {
				_PlaneWidget->sliceIndex[_PlaneWidget->GetAxis()] = _Slice;
				_PlaneWidget->ViewDicom(_PlaneWidget->GetAxis());
				std::string msg = StatusMessage::Format(_Slice, _MaxSlice, _PlaneWidget->GetPlaneOrientation());
				_StatusMapper->SetInput(msg.c_str());
				this->worldPosition = _PlaneWidget->GetCellPicker()->GetPickPosition();
				_PlaneWidget->GetDefaultRenderer()->Render();
				std::cout << "Pick Position is : ( " << worldPosition[0] << " ," << worldPosition[1] << " ," << worldPosition[2] << " ) " << std::endl;
				cout << "PlaneWidgetDefaultRenderer is : " << _PlaneWidget->GetDefaultRenderer()->GetObjectName() << endl;
				cout << "PlaneWidgetCurrentRenderer is : " << _PlaneWidget->GetCurrentRenderer()->GetObjectName() << endl;
			}
		}

	}

	void MoveSliceBackward()
	{
		if (_Slice > _MinSlice)
		{
			_Slice -= 1;
			cout << "MoveSliceBackward : " << _Slice << endl;
			_ImageViewer->SetSlice(_Slice);
			std::string msg = StatusMessage::Format(_Slice, _MaxSlice, _ImageViewer->GetSliceOrientation());
			_StatusMapper->SetInput(msg.c_str());
			_ImageViewer->Render();
		}
	}

	virtual void OnLeftButtonDown() override
	{
		MoveSliceForward();
		cout << "PlaneWidgetPosition is : " << _PlaneWidget->GetSlicePosition() << endl;

		cout << "Next  : " << _Slice << endl;
	};

	virtual void OnRightButtonDown() override
	{
		MoveSliceBackward();
		cout << "Previous : " << _Slice << endl;
	}

};