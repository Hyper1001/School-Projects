#include "entrydialog.h"
#include "mainwin.h"
#include <iostream>

Mainwin:: Mainwin()
{
    store = nullptr;
    message = nullptr;
    msg = nullptr;
    set_default_size(1920,1080);
    set_title("ELSA -  Exceptional Laptops and Supercomputers Always")
    Gtk::Box *vbox = Gtk::manage(new Gtk::Vbox);
    add(*vbox);
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    Gtk::MenuItem *quitMenu = Gtk::manage(new Gtk::MenuItem{"_Quit",true});
    quitMenu ->signal_activate().connect([this]{this->on_quit_click();});
    menubar ->append(*quitMenu);

    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_View", true));
    Gtk::Menu *viewMenu = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem *viewCustomer = Gtk::manage(new Gtk::MenuItem("Customer", false));
    viewCustomer -> signal_activate().connect([this]{this->on_view_customer_click();});
    Gtk::MenuItem *viewPeripheral = Gtk::manage(new Gtk::MenuItem("Periphral", false));
    viewCustomer -> signal_activate().connect([this]{this->on_view_peripheral_click();});
    Gtk::MenuItem *viewCustomer = Gtk::manage(new Gtk::MenuItem("Desktop", false));
    viewCustomer -> signal_activate().connect([this]{this->on_view_desktop_click();});
    Gtk::MenuItem *viewCustomer = Gtk::manage(new Gtk::MenuItem("Order", false));
    viewCustomer -> signal_activate().connect([this]{this->on_view_order_click();});
    menubar->append(*menuitem_new);
    menuitem_new ->set_submenu(*viewMenu);
    viewMenu -> append(*on_view_customer_click());
	viewMenu -> append(*on_view_peripheral_click());
	viewMenu -> append(*on_view_desktop_click());
	viewMenu -> append(*on_view_order_click());

    Gtk::MenuItem *menuitem_new2 = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    Gtk::Menu *insertMenu = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem *insertCustomer = Gtk::manage(new Gtk::MenuItem("Customer", false));
    insertCustomer -> signal_activate().connect([this]{this->on_insert_customer_click();});
    Gtk::MenuItem *insertPeripheral = Gtk::manage(new Gtk::MenuItem("Periphral", false));
    insertCustomer -> signal_activate().connect([this]{this->on_insert_peripheral_click();});
    Gtk::MenuItem *insertCustomer = Gtk::manage(new Gtk::MenuItem("Desktop", false));
    insertCustomer -> signal_activate().connect([this]{this->on_insert_desktop_click();});
    Gtk::MenuItem *insertCustomer = Gtk::manage(new Gtk::MenuItem("Order", false));
    viewCustomer -> signal_activate().connect([this]{this->on_insert_order_click();});
    menubar->append(*menuitem_new2);
    menuitem_new ->set_submenu(*insertMenu);
    insertMenu -> append(*on_insert_customer_click());
	insertMenu -> append(*on_insert_peripheral_click());
	insertMenu -> append(*on_insert_desktop_click());
	insertMenu -> append(*on_insert_order_click());

    Gtk::MenuItem *menuitem_new3 = Gtk::manage(new Gtk::MenuItem("_Help", true));
    Gtk::Menu *helpMenu = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem *aboutMenu = Gtk::manage(new Gtk::MenuItem("About", false));
    menubar->append(*menuitem_new3);
    menuitem_new3 ->set_submenu(*helpMenu);
    helpMenu -> append(*aboutMenu);
    aboutMenu ->signal_activate().connect([this]{this->on_about_click();});

    data = Gtk::manage(new Gtk::Label);
    data -> set_vexpand(true);
    data -> set_hexpand(true);
    data -> set_alignment(Gtk::ALIGN_START,Gtk::ALIGN_START);
    vbox-> add(*data);
    msg = Gtk::manage(new Gtk::Label);
    msg -> set_vexpand(true);
    msg -> set_hexpand(true);
    vbox-> pack_start(*msg,Gtk::PACK_SHIRNK,0)l
    vbox->show_all();
    store = new Store();
}

Mainwin::~Mainwin()
{
    delete(store);//frees store from memory
}


void Mainwin::on_quit_click()
{
    close();
}
