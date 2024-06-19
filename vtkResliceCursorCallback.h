#pragma once
class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback* New()
	{
		return new vtkResliceCursorCallback;
	}

	void Execute(vtkObject* caller, unsigned long, void* callData) override
	{
		vtkResliceCursorWidget* rcw = dynamic_cast<vtkResliceCursorWidget*>(caller);

		if (rcw)
		{
			vtkResliceCursorRepresentation* rep = dynamic_cast<vtkResliceCursorLineRepresentation*>(rcw->GetRepresentation());
			// vtkResliceCursor *rc = rep->GetResliceCursorActor()->GetCursorAlgorithm()->GetResliceCursor();

			for (int i = 0; i < 3; i++)
			{

				cout << rcw->GetResliceCursorRepresentation()->GetReslice() << endl;
			}

		}
		this->RCW[0]->Render();
	}
	vtkResliceCursorCallback() {}
	vtkResliceCursorWidget* RCW[3];
};

vtkStandardNewMacro(testInteractor);
vtkStandardNewMacro(CellPickingInteractorStyle);
vtkStandardNewMacro(ImageViewerInteractorStyle);
vtkStandardNewMacro(MprImageViewer);
vtkStandardNewMacro(RscMprWidget);
vtkStandardNewMacro(IpwMprWidget);
