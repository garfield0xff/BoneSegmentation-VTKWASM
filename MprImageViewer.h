#pragma once

class MprImageViewer : public vtkImageViewer2
{
public:
	static MprImageViewer* New();
	vtkTypeMacro(MprImageViewer, vtkImageViewer2);
	// void PrintSelf(ostream os, vtkIndent indent)override;

private:
	vtkNew<vtkTextProperty> sliceTextProp;
	vtkNew<vtkTextMapper> sliceTextMapper;
	vtkNew<vtkActor2D> sliceTextActor;

public:
	void SetText()
	{
		std::string msg = StatusMessage::Format(this->GetSliceMin(), this->GetSliceMax(), this->GetSliceOrientation());

		sliceTextProp->SetFontSize(5);
		sliceTextProp->SetVerticalJustificationToBottom();
		sliceTextProp->SetJustificationToLeft();

		sliceTextMapper->SetInput(msg.c_str());
		sliceTextMapper->SetTextProperty(sliceTextProp);

		sliceTextActor->SetMapper(sliceTextMapper);
		sliceTextActor->SetPosition(15, 10);

		this->GetRenderer()->AddActor2D(sliceTextActor);

	}

	vtkSmartPointer<vtkTextMapper> GetTextMapper() { return this->sliceTextMapper; }

};
