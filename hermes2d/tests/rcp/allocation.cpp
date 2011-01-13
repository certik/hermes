#include "hermes2d.h"

using Teuchos::RCP;
using Teuchos::Ptr;
using Teuchos::rcp;
using Teuchos::null;

class MyMesh {
public:
    MyMesh() {
        printf("MyMesh() created\n");
    }
    ~MyMesh() {
        printf("MyMesh() deleted\n");
    }
    void run() {
        printf("run() called\n");
    }
};

int main(int argc, char* argv[])
{
    // Regular approach using stack:
    {
        RCP<MyMesh> m = rcp(new MyMesh());
        m->run();
    }

    // Cython approach using heap:
    {
        RCP<MyMesh> *m = new RCP<MyMesh>(new MyMesh());
        (*m)->run();
        delete m;
    }

    return ERR_SUCCESS;
}
