#pragma once

class testInteractor : public vtkCommand
{
protected:
	testInteractor() {}

public:
	static testInteractor* New();
	virtual ~testInteractor() {}

	void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> pInter)
	{
		this->m_pInteractor = pInter;
		if (nullptr == this->m_pInteractor)return;

		m_pInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::LeftButtonReleaseEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::RightButtonPressEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::RightButtonReleaseEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::MiddleButtonPressEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::MouseMoveEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::MouseWheelForwardEvent, this, 1.0f);
		m_pInteractor->AddObserver(vtkCommand::MouseWheelBackwardEvent, this, 1.0f);

	}

	void SetInteractorStyles(vtkNew<ImageViewerInteractorStyle> _ImageViewerInteractorStyle[3])
	{
		for (unsigned i = 0; i < 3; i++)this->_ImageViewerInteractorStyle[i] = _ImageViewerInteractorStyle[i];
	}

	void SetCellPickingStyle(vtkSmartPointer<CellPickingInteractorStyle> _CellPickingStyle)
	{
		this->cp_style = _CellPickingStyle;
	}


	vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() const { return m_pInteractor; };


protected:

	virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
	{
		auto pInter = this->GetInteractor();
		if (nullptr == pInter) return;

		auto iPos = pInter->GetEventPosition();
		auto pRen = pInter->FindPokedRenderer(iPos[0], iPos[1]);
		if (nullptr == pRen) return;

		bool isLeftButtonPressed = (eventId == vtkCommand::LeftButtonPressEvent);
		bool isLeftButtonReleased = (eventId == vtkCommand::LeftButtonReleaseEvent);
		bool isRightButtonPressed = (eventId == vtkCommand::RightButtonPressEvent);
		bool isRightButtonReleased = (eventId == vtkCommand::RightButtonReleaseEvent);
		bool isMiddleButtonPressed = (eventId == vtkCommand::MiddleButtonPressEvent);
		bool isMiddleButtonReleased = (eventId == vtkCommand::MiddleButtonReleaseEvent);
		bool isMouseMove = (eventId == vtkCommand::MouseMoveEvent);
		bool isMouseWheelForward = (eventId == vtkCommand::MouseWheelForwardEvent);
		bool isMouseWheelBackward = (eventId == vtkCommand::MouseWheelBackwardEvent);

		if (pRen->GetObjectName() == "renderer0")
		{
			pRen->GetRenderWindow()->GetInteractor()->SetInteractorStyle(this->_ImageViewerInteractorStyle[0]);
		}
		else if (pRen->GetObjectName() == "renderer1")
		{
			pRen->GetRenderWindow()->GetInteractor()->SetInteractorStyle(this->_ImageViewerInteractorStyle[1]);
		}
		else if (pRen->GetObjectName() == "renderer2")
		{
			pRen->GetRenderWindow()->GetInteractor()->SetInteractorStyle(this->_ImageViewerInteractorStyle[2]);
		}
		else if (pRen->GetObjectName() == "renderer3")
		{
			// if(pRen->GetObjectName() != "renderer3"){ auto pRen = pInter->FindPokedRenderer(iPos[0], iPos[1]);}
			pRen->GetRenderWindow()->GetInteractor()->SetInteractorStyle(this->cp_style);
		}
	}

private:
	vtkSmartPointer<vtkRenderWindowInteractor> m_pInteractor;
	vtkSmartPointer<vtkRenderer> renderer[3];


	vtkSmartPointer<RscMprWidget> _RscMprWidget[3];
	IpwMprWidget _IpwMprWidget[3];


	vtkSmartPointer<ImageViewerInteractorStyle> _ImageViewerInteractorStyle[3];


	vtkNew<vtkInteractorStyleImage> i_style[3];
	vtkSmartPointer<CellPickingInteractorStyle> cp_style;
	vtkNew<vtkInteractorStyleTrackballCamera> tbc_style;
	vtkNew<vtkInteractorStyleSwitch> switch_style;


	int imageIndex = 0;


};