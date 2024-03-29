#include "mainwin.h"
#include "entrydialog.h"
#include <sstream>
#include <iomanip>

Mainwin::Mainwin() : store{new Store}, fileName{"untitled.elsa"} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);
    set_title("ELSA");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // /////// ////////////////////////////////////////////////////////////////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::Menu *menu = Gtk::manage(new Gtk::Menu);
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    Gtk::MenuItem *menuitem_open = Gtk::manage(new Gtk::MenuItem{"_Open", true});
	Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem{"_Save", true});
	Gtk::MenuItem *menuitem_save_as = Gtk::manage(new Gtk::MenuItem{"Save As", false});
    menuitem_open -> signal_activate().connect([this] {this -> on_open_click();});
	menuitem_save -> signal_activate().connect([this] {this -> on_save_click();});
	menuitem_save_as -> signal_activate().connect([this] {this -> on_save_as_click();});

    menubar->append(*menuitem_file);
    menu -> append(*openMenuItem);
	menu -> append(*saveMenuItem);
	menu -> append(*saveAsMenuItem);

    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

    //     V I E W
    // Create a View menu and add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    //         C U S T O M E R
    // Append Customer to the View menu
    Gtk::MenuItem *menuitem_view_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_view_customer->signal_activate().connect([this] {this->on_view_customer_click();});
    viewmenu->append(*menuitem_view_customer);

    //         P E R I P H E R A L S
    // Append Peripheral to the View menu
    Gtk::MenuItem *menuitem_view_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_view_peripheral->signal_activate().connect([this] {this->on_view_peripheral_click();});
    viewmenu->append(*menuitem_view_peripheral);

    //         D E S K T O P
    // Append Desktop to the View menu
    Gtk::MenuItem *menuitem_view_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_view_desktop->signal_activate().connect([this] {this->on_view_desktop_click();});
    viewmenu->append(*menuitem_view_desktop);

    //         O R D E R
    // Append Order to the View menu
    Gtk::MenuItem *menuitem_view_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_view_order->signal_activate().connect([this] {this->on_view_order_click();});
    viewmenu->append(*menuitem_view_order);

    //     I N S E R T
    // Create a Insert menu and add to the menu bar
    Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);

    //         C U S T O M E R
    // Append Customer to the Insert menu
    Gtk::MenuItem *menuitem_insert_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_insert_customer->signal_activate().connect([this] {this->on_insert_customer_click();});
    insertmenu->append(*menuitem_insert_customer);

    //         P E R I P H E R A L S
    // Append Peripheral to the Insert menu
    Gtk::MenuItem *menuitem_insert_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_insert_peripheral->signal_activate().connect([this] {this->on_insert_peripheral_click();});
    insertmenu->append(*menuitem_insert_peripheral);

    //         D E S K T O P
    // Append Desktop to the Insert menu
    Gtk::MenuItem *menuitem_insert_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_insert_desktop->signal_activate().connect([this] {this->on_insert_desktop_click();});
    insertmenu->append(*menuitem_insert_desktop);

    //         O R D E R
    // Append Order to the Insert menu
    Gtk::MenuItem *menuitem_insert_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_insert_order->signal_activate().connect([this] {this->on_insert_order_click();});
    insertmenu->append(*menuitem_insert_order);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           E A S T E R
    // Append Easter Egg to the Help menu
    Gtk::MenuItem *menuitem_easter = Gtk::manage(new Gtk::MenuItem("_Easter Egg", true));
    menuitem_easter->signal_activate().connect([this] {this->on_easter_egg_click();});
    helpmenu->append(*menuitem_easter);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);

    // /////////////////////////// ////////////////////////////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining sticks
    data = Gtk::manage(new Gtk::Label{"", Gtk::ALIGN_START, Gtk::ALIGN_START});
    data->set_hexpand();
    // A Gtk::Label is intrinsically transparent - it's background color cannot be set
    // Therefore, we add it to a Gtk::EventBox with background color overridden to white
    Gtk::EventBox *eb = Gtk::manage(new Gtk::EventBox);
    eb->set_hexpand();
    eb->override_background_color(Gdk::RGBA("white"));
    eb->add(*data);
    // PACK_EXPAND_WIDGET tells VBox this widget should be as big as possible
    vbox->pack_start(*eb, Gtk::PACK_EXPAND_WIDGET, 0);

    // S T A T U S   B A R   D I S P L A Y ////////////////////////////////////
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label);
    msg->set_hexpand();
    // PACK_SHRINK tells VBox this widget should be as small as possible
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click() {
    close();
}

// These 4 methods use an output string stream for format data for display
// They are invoked by the user via the View menu, and also by the program
//     when the user needs to select one, e.g., for an order
void Mainwin::on_view_peripheral_click() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Peripherals</b></big><tt>\n\n";
    for(int i=0; i<store->num_options(); ++i)
        oss << i << ") " << store->option(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}
void Mainwin::on_view_desktop_click() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Products</b></big><tt>\n\n";
    for(int i=0; i<store->num_desktops(); ++i)
        oss << i << ") " << store->desktop(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}
void Mainwin::on_view_order_click() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Orders</b></big><tt>\n\n";
    for(int i=0; i<store->num_orders(); ++i)
        oss << i << ") " << store->order(i) << "\n\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}
void Mainwin::on_view_customer_click() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Customers</b></big><tt>\n\n";
    for(int i=0; i<store->num_customers(); ++i)
        oss << i << ") " << store->customer(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}

// These methods insert new data into the containers
// They work exactly like the command line version, except
//     they use dialogs (via get_string et al).
void Mainwin::on_insert_peripheral_click() {
    std::string peripheral = get_string("Name of new peripheral?");
    double cost = get_double("Cost?");

    Options option{peripheral, cost};
    store->add_option(option);

    on_view_peripheral_click();
    set_msg("Added peripheral " + peripheral);
}
void Mainwin::on_insert_desktop_click() {
    on_view_peripheral_click();
    int desktop = store->new_desktop();
    while(true) {
        std::ostringstream oss;
        oss << store->desktop(desktop) << "\n\nAdd which peripheral (-1 when done)? ";

        int option = get_int(oss.str());

        if(option == -1) break;
        try {
            store->add_option(option, desktop);
        } catch(std::exception& e) {
            Gtk::MessageDialog{*this, "#### INVALID OPTION ####\n\n"}.run();
        }
    }
    on_view_desktop_click();
    set_msg("Added desktop " + std::to_string(desktop));
}
void Mainwin::on_insert_order_click() {
    on_view_customer_click();

    int customer = get_int("Customer?");
    if(customer == -1) return;

    int order = store->new_order(customer);

    on_view_desktop_click();
    while(true) {
        int desktop = get_int("Desktop (-1 when done)?");

        if(desktop == -1) break;
        store->add_desktop(desktop, order);
    }

    on_view_order_click();
    set_msg("Added order " + std::to_string(order) + " for $" + std::to_string(store->order(order).price()));
}
void Mainwin::on_insert_customer_click() {
    std::string name = get_string("Customer name?");
    if(name.size()) {
        std::string phone = get_string("Customer phone (xxx-xxx-xxxx)?");
        std::string email = get_string("Customer email (xxx@domain.com)?");

        Customer customer{name, phone, email};
        store->add_customer(customer);
    }
    on_view_customer_click();
    set_msg("Added customer " + name);

}
void Mainwin::on_easter_egg_click() {
    Customer c{"Bugs Bunny", "817-ACA-RROT", "bugs@loony.tunes"};          store->add_customer(c);
    c = Customer{"Elastigirl", "817-STR-ETCH", "helen@incredibles.movie"}; store->add_customer(c);
    c = Customer{"Tuck and Roll", "817-UFI-RED2", "circus@bugs.life"};     store->add_customer(c);
    c = Customer{"Tiana", "817-NOG-RIMM", "princess@lily.pad"};            store->add_customer(c);

    Options o{"CPU: 2.6 GHz Xeon 6126T", 2423.47};         store->add_option(o);
    o = Options{"CPU: 2.4 GHz Core i7-8565U", 388.0};      store->add_option(o);
    o = Options{"CPU: 2.2 GHz AMD Opteron", 37.71};        store->add_option(o);
    o = Options{"CPU: 300 MHz AM3351BZCEA30R ARM", 11.03}; store->add_option(o);
    o = Options{"CPU: 240 MHz ColdFire MCF5", 17.33};      store->add_option(o);

    o = Options{"2 GB RAM", 17.76};                        store->add_option(o);
    o = Options{"4 GB RAM", 22.95};                        store->add_option(o);
    o = Options{"8 GB RAM", 34.99};                        store->add_option(o);
    o = Options{"16 GB RAM", 92.99};                       store->add_option(o);
    o = Options{"32 GB RAM", 134.96};                      store->add_option(o);
    o = Options{"64 GB RAM", 319.99};                      store->add_option(o);

    o = Options{"0.5 TB SSD", 79.99};                      store->add_option(o);
    o = Options{"1 TB SSD", 109.99};                       store->add_option(o);
    o = Options{"2 TB SSD", 229.99};                       store->add_option(o);
    o = Options{"4 TB SSD", 599.99};                       store->add_option(o);

    o = Options{"1 TB PC Disk", 44.83};                    store->add_option(o);
    o = Options{"2 TB Hybrid Disk", 59.99};                store->add_option(o);
    o = Options{"4 TB Hybrid Disk", 93.98};                store->add_option(o);

    int desktop = store->new_desktop();
    store->add_option(0, desktop);
    store->add_option(9, desktop);
    store->add_option(14, desktop);

    desktop = store->new_desktop();
    store->add_option(1, desktop);
    store->add_option(7, desktop);
    store->add_option(17, desktop);

    desktop = store->new_desktop();
    store->add_option(5, desktop);
    store->add_option(7, desktop);
    store->add_option(15, desktop);
}

// This is Help > About
void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("ELSA");
    auto logo = Gdk::Pixbuf::create_from_file("elsa.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 0.2.0");
    dialog.set_copyright("Copyright 2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"George F. Rice"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {"Custom logo based on public domain image\nhttps://www.piqsels.com/en/public-domain-photo-ffxdb"};
    dialog.set_artists(artists);
    dialog.run();
    set_msg("");
}

// /////////////////
// U T I L I T I E S
// /////////////////
// These utilities write data to the main window
void Mainwin::set_data(std::string s) {data->set_markup(s);}
void Mainwin::set_msg(std::string s) {msg->set_markup(s);}

// These utilities use a dialog to read a string, double, or int
//     from the user
std::string Mainwin::get_string(std::string prompt) {
    EntryDialog ed_string{*this, prompt};
    ed_string.run();
    return ed_string.get_text();
}
double Mainwin::get_double(std::string prompt) {
    try {
        return std::stod(get_string(prompt));
    } catch(std::exception& e) {
        // std::MessageDialog{*this, "ERROR: Invalid double"}.run();
        return -1.0;
    }
}
int Mainwin::get_int(std::string prompt) {
    try {
        return std::stoi(get_string(prompt));
    } catch(std::exception& e) {
        // std::MessageDialog{*this, "ERROR: Invalid int"}.run();
        return -1;
    }
}


