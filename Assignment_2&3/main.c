#include "UserInterface.h"
#include "Tests.h"

int main(){
    test_all();
    UserInterface* user_interface = create_user_interface();
    start_user_interface(user_interface);
    destroy_user_interface(user_interface);
    return 0;
}
