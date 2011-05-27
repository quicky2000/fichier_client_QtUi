#include "main_window.h"
#include "test.h"
#include "my_date_widget.h"

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
main_window::main_window(void):
  m_import_file_action(NULL),
  m_open_file_action(NULL),
  m_save_action(NULL),
  m_save_as_action(NULL),
  m_close_action(NULL),
  m_exit_action(NULL),
  m_test_action(NULL),
  m_file_menu(NULL),
  m_status_label(NULL),
  m_name_field(NULL),
  m_first_name_field(NULL),
  m_city_field(NULL),
  m_client_list_table(NULL),
  m_achat_list_table(NULL)
{
  QWidget *l_widget = new QWidget;
  setCentralWidget(l_widget);
  
  setWindowTitle(tr("Fichier client"));
  create_actions();
  create_menus();
  create_status_bar();

  QFrame * l_frame = new QFrame();
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(l_frame);
  QHBoxLayout *layout = new QHBoxLayout(l_frame);
  l_vertical_layout->addLayout(layout);

  layout->addWidget(new QLabel(tr("Name")+" :"));

  m_name_field = new QLineEdit("");
  layout->addWidget(m_name_field);
  connect(m_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));

  layout->addWidget(new QLabel(tr("First Name")+" :"));

  m_first_name_field = new QLineEdit("");
  layout->addWidget(m_first_name_field);
  connect(m_first_name_field,SIGNAL(textEdited(const QString&)),this, SLOT(criteria_modification()));


  layout->addStretch();
  layout->addWidget(new QLabel(tr("City")+" :"));

  m_city_field = new QLineEdit("");
  layout->addWidget(m_city_field);
  connect(m_city_field,SIGNAL(textEdited(const QString &)),this, SLOT(criteria_modification()));

  l_vertical_layout->addWidget(new QLabel("Client search results :"));

  m_client_list_table = new client_list_table(l_frame);
  l_vertical_layout->addWidget(m_client_list_table);
  connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(client_selected(int)));

  l_vertical_layout->addWidget(new QLabel("Achats for selected client :"));

  m_achat_list_table = new achat_list_table(l_frame);
  l_vertical_layout->addWidget(m_achat_list_table);

  my_date_widget * l_date_widget = new my_date_widget();
  //  l_vertical_layout->addWidget(l_date_widget);


  //  connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(client_selected(int)));

  setCentralWidget(l_frame);

  manage_features(false);

  setMinimumSize(160, 160);
  resize(800, 600);
}

void main_window::manage_features(bool p_enable)
{
  m_name_field->setEnabled(p_enable);
  m_first_name_field->setEnabled(p_enable);
  m_city_field->setEnabled(p_enable);

  m_name_field->setText("");
  m_first_name_field->setText("");
  m_city_field->setText("");   

  m_client_list_table->clearContents();
  m_achat_list_table->clearContents();      
}


//------------------------------------------------------------------------------
void main_window::create_actions(void)
{
  m_import_file_action = new QAction(tr("&Import"),this);
  m_import_file_action->setShortcut(tr("Ctrl+I"));
  m_import_file_action->setStatusTip(tr("Import a file from MySql")); 
  connect(m_import_file_action,SIGNAL(triggered()),this,SLOT(import()));

  m_open_file_action = new QAction(tr("&Open"),this);
  m_open_file_action->setShortcut(tr("Ctrl+O"));
  m_open_file_action->setStatusTip(tr("Open a file")); 
  connect(m_open_file_action,SIGNAL(triggered()),this,SLOT(open_db()));

  m_save_action = new QAction(tr("&Save"),this);
  m_save_action->setShortcut(tr("Ctrl+S"));
  m_save_action->setStatusTip(tr("Save current file")); 
  connect(m_save_action,SIGNAL(triggered()),this,SLOT(save()));

  m_save_as_action = new QAction(tr("&Save As"),this);
  m_save_as_action->setShortcut(tr("Ctrl+E"));
  m_save_as_action->setStatusTip(tr("Save a file with a new name")); 
  connect(m_save_as_action,SIGNAL(triggered()),this,SLOT(save_as()));

  m_close_action = new QAction(tr("&Close"),this);
  m_close_action->setShortcut(tr("Ctrl+C"));
  m_close_action->setStatusTip(tr("Close current file")); 
  connect(m_close_action,SIGNAL(triggered()),this,SLOT(close_db()));

  m_test_action = new QAction(tr("&Test"),this);
  m_test_action->setShortcut(tr("Ctrl+T"));
  m_test_action->setStatusTip(tr("Launch test actions")); 
  connect(m_test_action,SIGNAL(triggered()),this,SLOT(test()));

  m_exit_action = new QAction(tr("&Quit"),this);
  m_exit_action->setShortcut(tr("Ctrl+Q"));
  m_exit_action->setStatusTip(tr("Quit the application")); 
  connect(m_exit_action,SIGNAL(triggered()),this,SLOT(exit()));
}

//------------------------------------------------------------------------------
void main_window::create_menus(void)
{
  m_file_menu = menuBar()->addMenu(tr("&File"));
  //  m_file_menu->addAction(m_import_file_action);
  m_file_menu->addAction(m_open_file_action);
  m_file_menu->addAction(m_save_action);
  m_file_menu->addAction(m_save_as_action);
  //  m_file_menu->addAction(m_test_action);
  m_file_menu->addAction(m_close_action);
  m_file_menu->addAction(m_exit_action);

  // Manage action activation
  m_import_file_action->setEnabled(true);
  m_open_file_action->setEnabled(true);
  m_save_action->setEnabled(false);
  m_save_as_action->setEnabled(false);
  m_test_action->setEnabled(false);
  m_close_action->setEnabled(false);
  m_exit_action->setEnabled(true);
}

//------------------------------------------------------------------------------
void main_window::create_status_bar(void)
{
  m_status_label = new QLabel("Status bar");
  statusBar()->addWidget(m_status_label);
}

//------------------------------------------------------------------------------
void main_window::test(void)
{
  test::test();
}

//------------------------------------------------------------------------------
void main_window::import(void)
{
  cout << "Import a file" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
                                   tr("Open Database"), ".",
                                   tr("Spreadsheet files (*.sql)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to import is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {

      m_import_file_action->setEnabled(false);
      m_open_file_action->setEnabled(false);
      m_save_as_action->setEnabled(true);
      m_close_action->setEnabled(true);

      m_fichier_client.import_external_sql(l_file_name_std);
      QMessageBox::information (this,"Import Status","File successfully imported", QMessageBox::Ok,QMessageBox::Ok);

      manage_features(true);
    }
}

//------------------------------------------------------------------------------
void main_window::open_db(void)
{
  cout << "Open a file" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
                                   tr("Open Database"), ".",
                                   tr("Fichier client files (*.sqlite3)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to open is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_import_file_action->setEnabled(false);
      m_open_file_action->setEnabled(false);
      m_save_action->setEnabled(true);
      m_save_as_action->setEnabled(true);
      m_close_action->setEnabled(true);

      m_fichier_client.open_db(l_file_name_std);
      QMessageBox::information (this,"Open Status","File successfully opened", QMessageBox::Ok,QMessageBox::Ok);
      manage_features(true);
     }
}

//------------------------------------------------------------------------------
void main_window::exit(void)
{
  cout << "Exit" << endl ;
  close();
}

//------------------------------------------------------------------------------
void main_window::save(void)
{
  cout << "Save" << endl ;
  m_fichier_client.save();
}

//------------------------------------------------------------------------------
void main_window::save_as(void)
{
  cout << "Save as" << endl ;
  
  QString l_file_name = QFileDialog::getSaveFileName(this,
                                   tr("Save Database"), ".",
                                   tr("Fichier client files (*.sqlite3)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to save is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_fichier_client.save_as(l_file_name_std);
      QMessageBox::information (this,"Save Status","File successfully saved", QMessageBox::Ok,QMessageBox::Ok);
      m_save_action->setEnabled(true);
    }
}

//------------------------------------------------------------------------------
void main_window::close_db(void)
{
  cout << "Close" << endl ;
  m_open_file_action->setEnabled(true);
  m_save_action->setEnabled(false);
  m_save_as_action->setEnabled(false);
  m_close_action->setEnabled(false);
  manage_features(false);
  m_fichier_client.close_db();
}


//------------------------------------------------------------------------------
void main_window::criteria_modification(void)
{
  cout << "Criteria modification" << endl ;
  string l_name = m_name_field->text().toStdString();
  string l_first_name = m_first_name_field->text().toStdString();
  string l_city = m_city_field->text().toStdString();
  cout << "Name = \"" << l_name << "\"\tFirst name = \"" << l_first_name << "\"\tCity = \"" << l_city << "\"" << endl ;
  vector<search_client_item> l_result ;
  m_fichier_client.search_client(l_name,l_first_name,l_city,l_result);
  m_client_list_table->update(l_result);
}

//------------------------------------------------------------------------------
void main_window::client_selected(int p_row)
{
  cout << "Row selected " << p_row << endl ;
  uint32_t l_client_id = m_client_list_table->get_selected_client_id(p_row);
  cout << "Id of selected client " << l_client_id << endl;
  vector<search_achat_item> l_list_achat;
  m_fichier_client.get_achat_by_client_id(l_client_id,l_list_achat);
  m_achat_list_table->update(l_list_achat);  
}

//------------------------------------------------------------------------------
void main_window::closeEvent(QCloseEvent *event)
{
  int l_result = QMessageBox::question(this, tr("Quit"),
				       tr("Are you sure want to quit ?"),
				       QMessageBox::Yes | QMessageBox::Default,
				       QMessageBox::No);
  if (l_result == QMessageBox::Yes)
    {
      event->accept();
    }
  else
    {
      event->ignore();
    }
}
//EOF
