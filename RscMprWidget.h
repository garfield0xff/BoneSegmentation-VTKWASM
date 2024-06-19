#pragma once

class RscMprWidget : public vtkResliceCursorWidget
{
public:
    static RscMprWidget* New();
    vtkTypeMacro(RscMprWidget, vtkResliceCursorWidget);

private:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkResliceCursorLineRepresentation> resliceCursorRep;
    vtkSmartPointer<vtkResliceCursorWidget> resliceCursorWidget;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkSmartPointer<vtkResliceCursor> resliceCursor;
    vtkImageData* imageData;
    vtkImagePlaneWidget* _IpwMprWidget;
    vtkImageViewer2* _ImageViewer;

    double minVal;
    double viewUp[3][3] = { { 0, 0, -1 }, { 0, 0, 1 }, { 0, 1, 0 } };
    double camPos[3] = { 0, 0, 0 };
    double camZoom[3] = { 2.2, 2.2, 1.8 };

    int sliceIndex[3] = { 0, 0, 0 };
    int axis;
    int imageDims[3];
    int currentSlice;
    int maxSlice;

public:
    RscMprWidget()
    {
        const double minVal = 0.0;
        this->resliceCursorRep = vtkSmartPointer<vtkResliceCursorLineRepresentation>::New();
        this->resliceCursor = vtkSmartPointer<vtkResliceCursor>::New();
        this->resliceCursorWidget = vtkSmartPointer<vtkResliceCursorWidget>::New();
    }

    void SetImageViewer(vtkImageViewer2* ImageViewer)
    {
        this->_ImageViewer = ImageViewer;
    }

    void SetIpwWidget(vtkImagePlaneWidget* IpwMprWidget)
    {
        this->_IpwMprWidget = IpwMprWidget;
    }

    void SetImageData(vtkImageData* imageData)
    {
        this->imageData = imageData;
    }

    void SetRWInteractor(vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor)
    {
        this->renderWindowInteractor = renderWindowInteractor;
    }

    void SetRenderer(vtkSmartPointer<vtkRenderer> renderer)
    {
        this->renderer = renderer;
    }

    void ViewDicom(int axis)
    {

        this->resliceCursor->SetCenter(this->imageData->GetCenter());
        this->resliceCursor->SetThickMode(1);
        this->resliceCursor->SetThickness(10, 10, 10);
        this->resliceCursor->SetImage(this->imageData);

        this->resliceCursorWidget->SetInteractor(this->renderWindowInteractor);
        this->resliceCursorWidget->SetRepresentation(this->resliceCursorRep);
        this->resliceCursorWidget->GetResliceCursorRepresentation()->GetReslice();

        cout << this->resliceCursorRep->GetResliceCursorActor()->GetClassName() << endl;
        this->resliceCursorRep->GetResliceCursorActor()->GetCursorAlgorithm()->SetResliceCursor(resliceCursor);
        this->resliceCursorRep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(axis);
        // this->resliceCursorRep->GetResliceCursorActor()->GetCenterlineProperty(axis)->SetRepresentationToWireframe();

        this->minVal = this->imageData->GetScalarRange()[0];

        if (vtkImageReslice* reslice = vtkImageReslice::SafeDownCast(resliceCursorRep->GetReslice()))
        {
            reslice->SetBackgroundColor(this->minVal, this->minVal, this->minVal, this->minVal);
        }

        this->resliceCursorWidget->SetDefaultRenderer(this->renderer);
        this->resliceCursorWidget->SetEnabled(1);

        this->renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
        this->renderer->SetBackground(0, 0, 0);

        this->camPos[axis] = 1;

        this->renderer->GetActiveCamera()->SetPosition(this->camPos);
        this->renderer->GetActiveCamera()->Zoom(camZoom[axis]);
        this->renderer->GetActiveCamera()->ParallelProjectionOn();
        this->renderer->GetActiveCamera()->SetViewUp(this->viewUp[axis][0], this->viewUp[axis][1], this->viewUp[axis][2]);
        this->renderer->ResetCamera();
    }
};
