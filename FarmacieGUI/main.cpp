
#include <QtWidgets/QApplication>
#include "myGUI.h"
#include "tests.h"
#include "repo.h"
#include "Reteta.h"
#include "service.h"
#include "validare.h"
#include "GUI.h"
#include "GUIModels.h"

int main(int argc, char *argv[])
{
    all_tests();
    {
        QApplication a(argc, argv);

        //Repository repo;
        RepoFile repo{ "medicamente.txt" };
        Validator valid;
        Reteta reteta{ repo };
        Service srv{ repo , valid , reteta };
        //myGUI gui{ srv, reteta };
        //gui.show();

        GUIModels gui{ srv, reteta };
        gui.show();

        return a.exec();
    }
 
}
