#include "VentanaDiseniador.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  VentanaDiseniador ventana;
  Gtk::Main::run(ventana);
  return 0;
}
