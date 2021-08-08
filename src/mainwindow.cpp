#include <mainwindow.h>
#include <application.h>

namespace AbyssCore{
    void Open(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find(new AString("empty")) == nullptr){
            mainWindow->window = new EmptyWindow();
            Application::GetGroup()->Create(mainWindow->window, new AString("empty"));
        }
    }
    void Hide(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find(new AString("empty")) != nullptr)
            mainWindow->window->SetVisible(!mainWindow->window->IsVisible());
    }

    void MoveAction(Widget* sender, ActionEvent event){
        EmptyWindow* empty = dynamic_cast<EmptyWindow*>(Application::GetGroup()->Find(new AString("empty")));

        if(empty != nullptr){
            SDL_Point pos = empty->pos;
            empty->pos = {pos.x + event.xrel, pos.y + event.yrel};
        }
    }

    void FullAction(Widget* sender, ActionEvent event){
        Window* parent = event.parent;

        parent->SetFull(!parent->IsFull());
    }

    MainWindow::MainWindow() : Window(){
        // open = new Button();
        // hide = new Button();
        // slide = new Button();
        full = new Button(this);
        trackbar = new Trackbar(this);

        // open->SetPos(10, 10);
        // open->SetSize(50, 50);

        // open->SetAction(Click, Open);

        // hide->SetPos(70, 10);
        // hide->SetSize(50, 50);

        // hide->SetAction(Click, Hide);

        // slide->SetPos(130, 10);
        // slide->SetSize(100, 100);

        // slide->SetAction(Drag, MoveAction);

        full->SetPos(240, 10);
        full->SetSize(50, 50);

        full->style.background = {RED};

        full->clickAction = FullAction;

        trackbar->SetPos(10, 10);
        trackbar->SetSize(200, 50);

        trackbar->maxValue = 1;
        trackbar->maxValue = 100;

        trackbar->SetValue(10);

        // AssignWidget(open, new AString("open"));
        // AssignWidget(hide, new AString("hide"));
        // AssignWidget(slide, new AString("move"));
        // AssignWidget(full, new AString("full"));
        AssignWidget(trackbar, new AString("trackbar"));

        currentSize = 200;
    }

    void MainWindow::Paint(Anchor anchor){
        Window::Paint(anchor);

        float scale = (float)trackbar->GetValue() / 10;
        int toSize = scale * 200;

        double odds = abs((double)toSize - currentSize);

        if(currentSize < toSize)
            currentSize += (odds * Application::deltaTime / 100);
        else if(currentSize > toSize)
            currentSize -= (odds * Application::deltaTime / 100);

        GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({anchor.x + 10, anchor.y + 70, (int)(round(currentSize)), (int)(round(currentSize))}), aColor({WHITE})), 4, ozzenVAO, ozzenVBO);

        textureShader->Use();

        textureShader->SetInt1(AString("flip"), 1);

        GLBind2DTexture(Application::ozzen);

        GLBindVertexArray(ozzenVAO);
        glDrawArrays(GL_QUADS, 0, 4);

        GLDestroyVertexObjects(ozzenVAO, ozzenVBO);

    }
}