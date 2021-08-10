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

        trackbar->SetPos(10, 10);
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

        float scale = (float)trackbar->GetValue() / 10;
        int toSize = scale * 200;

        double odds = abs((double)toSize - currentSize);

        if(currentSize < toSize)
            currentSize += (odds * Time::deltaTime / 100);
        else if(currentSize > toSize)
            currentSize -= (odds * Time::deltaTime / 100);

        GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({anchor.x + 10, anchor.y + 70, (int)(round(currentSize)), (int)(round(currentSize))}), aColor({WHITE})), 4, ozzenVAO, ozzenVBO);

        textureShader->Use();

        textureShader->SetInt1("flip", 1);

        GLBind2DTexture(Resources::GetTexture("ozzen").id);

        GLBindVertexArray(ozzenVAO);
        glDrawArrays(GL_QUADS, 0, 4);

        GLDestroyVertexObjects(ozzenVAO, ozzenVBO);

        Texture text = Resources::CreateStringTexture("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer eleifend justo dolor, non bibendum massa cursus eget. Ut hendrerit nibh eros, ut efficitur justo egestas in. Vestibulum consectetur euismod dapibus. Quisque nec elit porta, venenatis quam vel, consectetur est. Nulla sed egestas ligula, id semper urna. Suspendisse eu tempus arcu, sed hendrerit mauris. Praesent est urna, rhoncus at sem ut, aliquam pretium massa. Proin tellus purus, auctor vitae tincidunt in, rutrum id velit. Donec at iaculis mi, quis cursus sem. Morbi vulputate venenatis mi, at ullamcorper justo ullamcorper id. Curabitur ultricies risus a dapibus pellentesque. \
            Fusce semper venenatis tristique. In at nibh libero. Cras sit amet mi augue. Cras feugiat vulputate posuere. Duis sodales quis ante a venenatis. Aenean maximus aliquet semper. Integer eget nunc nec neque eleifend scelerisque. Pellentesque molestie auctor eros, malesuada eleifend velit fermentum in. Morbi eu enim ultrices, porttitor tellus at, ornare nulla. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. \
            Duis et nisi in felis ullamcorper fringilla tempus ac erat. Donec placerat nulla sapien, suscipit congue lectus sollicitudin nec. Quisque ut luctus erat. Aliquam efficitur sed dolor sed fermentum. Nulla facilisi. Curabitur odio velit, vehicula ac vehicula pulvinar, tempus eu nibh. Nam in lorem diam. Duis at mauris at metus placerat semper. Donec faucibus auctor lacus id ullamcorper. Nulla fermentum vitae libero vel eleifend. Donec ut massa est. Donec elementum dignissim nunc, quis auctor ipsum convallis ut. Integer et ligula non odio vehicula vulputate placerat vitae tortor. Phasellus pellentesque massa augue, vel congue ante vulputate at. Donec a urna vel justo luctus mollis eu ac sapien. Donec a ligula tortor. \
            Aliquam lacinia purus in ligula consectetur elementum. Nullam auctor gravida ante eget tincidunt. Sed vel nibh quis nisi sodales suscipit. Aliquam sagittis, libero at blandit blandit, risus nunc euismod nulla, ac luctus felis lectus vitae leo. Praesent blandit tincidunt leo at pretium. Sed facilisis pulvinar nulla id viverra. Duis aliquam, mauris ut aliquam consectetur, quam odio placerat orci, at tempor odio eros nec elit. Sed dictum elit non eros rutrum, vel imperdiet ex dictum. Nunc sed enim iaculis, convallis libero sed, scelerisque massa. Suspendisse ullamcorper efficitur sapien nec consectetur. \
            Donec id dui nulla. Nulla euismod quis odio at pellentesque. Integer sit amet fringilla magna. Vivamus magna diam, sagittis nec ultrices id, lacinia at sapien. Phasellus scelerisque lorem nunc, tempor tincidunt dui ultricies quis. Curabitur sapien ligula, vestibulum vitae tempus eu, interdum sed magna. Vestibulum lobortis, augue a hendrerit convallis, urna risus volutpat lorem, ut rutrum neque sapien ut lectus.", "firacode15");

        unsigned int VAO, VBO;

        GLCreateVertexObjects(GLCreateRectArray(SDL_Rect({anchor.x + 300, anchor.y + 10, text.width, text.height}), aColor({WHITE})), 4, VAO, VBO);

        GLBindVertexArray(VAO);

        GLBind2DTexture(text.id);

        glDrawArrays(GL_QUADS, 0 ,4);

        GLDestroyVertexObjects(VAO, VBO);
    }
}