#include <mainwindow.h>
#include <application.h>

namespace AbyssCore{
    void Open(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find("empty") == nullptr){
            mainWindow->window = new EmptyWindow();
            Application::GetGroup()->Create(mainWindow->window, "empty");
        }
    }
    void Hide(Widget* sender, ActionEvent event){
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(event.parent);

        if(Application::GetGroup()->Find("empty") != nullptr)
            mainWindow->window->SetVisible(!mainWindow->window->IsVisible());
    }

    void MoveAction(Widget* sender, ActionEvent event){
        EmptyWindow* empty = dynamic_cast<EmptyWindow*>(Application::GetGroup()->Find("empty"));

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

        trackbar->SetPos(10, 30);
        trackbar->SetSize(200, 50);

        trackbar->minValue = 1;
        trackbar->maxValue = 10;

        trackbar->SetValue(1);

        // AssignWidget(open, new AString("open"));
        // AssignWidget(hide, new AString("hide"));
        // AssignWidget(slide, new AString("move"));
        // AssignWidget(full, new AString("full"));
        AssignWidget(trackbar, "trackbar");

        currentSize = 200;
    }

    void MainWindow::Paint(Anchor anchor){
        Window::Paint(anchor);

        Clear(anchor, aColor({RED}));

        // float scale = (float)trackbar->GetValue() / 10;
        // int toSize = scale * 200;

        // double odds = abs((double)toSize - currentSize);

        // if(currentSize < toSize)
        //     currentSize += (odds * Time::deltaTime / 100);
        // else if(currentSize > toSize)
        //     currentSize -= (odds * Time::deltaTime / 100);

        // GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({anchor.x + 10, anchor.y + 70, (int)(round(currentSize)), (int)(round(currentSize))}), aColor({WHITE})), 4, ozzenVAO, ozzenVBO);

        // textureShader->Use();

        // textureShader->SetInt1("flip", 1);

        // GLBind2DTexture(Resources::GetTexture("ozzen").id);

        // glBindVertexArray(ozzenVAO);
        // glDrawArrays(GL_QUADS, 0, 4);

        // GLDestroyVertexObjects(ozzenVAO, ozzenVBO);

        // GLRenderText("To start game tou should press play button", "arial15", aPoint({anchor.x + 300, anchor.y + 30}));

        // Texture text = Resources::CreateStringTexture("Hellog world!!!", "arial30");

        // unsigned int VAO, VBO;

        // textureShader->Use();
        // textureShader->SetInt1("flip", 1);

        // GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({anchor.x + 10, anchor.y, text.width, text.height}), aColor({WHITE})), 4, VAO, VBO);

        // GLBindVertexArray(VAO);

        // GLBind2DTexture(text.id);

        // glDrawArrays(GL_QUADS, 0 ,4);

        // GLDestroyVertexObjects(VAO, VBO);
    }
}