#include "main_window.h"
#include "test.h"
#include "my_date_widget.h"
#include "search_widget.h"
#include "livre_facture_widget.h"
#include "facture_status_widget.h"
#include "facture_reason_widget.h"

#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMenuBar>
#include <QDialog>

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
  m_search_widget(NULL),
  m_livre_facture_widget(NULL),
  m_facture_status_widget(NULL),
  m_facture_reason_widget(NULL)
{
  setWindowTitle(tr("Fichier client"));
  create_actions();
  create_menus();
  create_status_bar();

  QTabWidget * m_tab_widget = new QTabWidget();

  m_livre_facture_widget = new livre_facture_widget(m_fichier_client);

  // Search widget
  m_search_widget = new search_widget(m_fichier_client);

  m_facture_status_widget = new facture_status_widget(m_fichier_client);

  m_facture_reason_widget = new facture_reason_widget(m_fichier_client);

  m_tab_widget->addTab(m_search_widget,tr("Search"));
  m_tab_widget->addTab(m_livre_facture_widget,tr("Livre facture"));
  m_tab_widget->addTab(m_facture_status_widget,tr("Facture status"));
  m_tab_widget->addTab(m_facture_reason_widget,tr("Facture reason"));

  setCentralWidget(m_tab_widget);

  manage_features(false);

  setMinimumSize(160, 160);
  resize(1000, 600);

  m_fichier_client.set_user_interface(this);
}

//------------------------------------------------------------------------------
void main_window::manage_features(bool p_enable)
{
  m_search_widget->set_enable(p_enable);
  m_livre_facture_widget->set_enable(p_enable);
  m_facture_status_widget->set_enable(p_enable);
  m_facture_reason_widget->set_enable(p_enable);
}

//---------------------------------------------------
// Methods inherited from fichier_client_UI_if class
//---------------------------------------------------
// Comunication with user
//------------------------------------------------------------------------------
void main_window::display_warning_message(const std::string & p_title,const std::string & p_text)
{
  QMessageBox::warning(this,p_title.c_str(),p_text.c_str(), QMessageBox::Ok,QMessageBox::Ok);
}

//------------------------------------------------------------------------------
void main_window::display_information_message(const std::string & p_title,const std::string & p_text)
{
  QMessageBox::information (this,p_title.c_str(),p_text.c_str(), QMessageBox::Ok,QMessageBox::Ok);
}

// Interactions with livre facture information
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void main_window::clear_livre_facture_information(void)
{
  m_livre_facture_widget->clear_livre_facture_information();
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_start_date(const std::string & p_date)
{
  m_livre_facture_widget->set_livre_facture_start_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_end_date(const std::string & p_date)
{
  m_livre_facture_widget->set_livre_facture_end_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_livre_facture_id(const std::string & p_id)
{
  m_livre_facture_widget->set_livre_facture_id(p_id);
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_start_date(void)const
{
  return m_livre_facture_widget->get_livre_facture_start_date();
}

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_start_date_complete(void)const
{
  return m_livre_facture_widget->is_livre_facture_start_date_complete();
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_end_date(void)const
{
  return m_livre_facture_widget->get_livre_facture_end_date();
}

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_end_date_complete(void)const
{
  return m_livre_facture_widget->is_livre_facture_end_date_complete();
}

//------------------------------------------------------------------------------
const std::string main_window::get_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_livre_facture_id();
}

// Interactions with livre facture list
//--------------------------------------

//------------------------------------------------------------------------------
bool main_window::is_livre_facture_selection_empty(void)const
{
  return m_livre_facture_widget->is_livre_facture_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_selected_livre_facture_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_livre_facture_list(std::vector<livre_facture> & p_list)
{
  m_livre_facture_widget->refresh_livre_facture_list(p_list);
}

// Interactions with livre facture actions
//-----------------------------------------
void main_window::set_delete_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_delete_livre_facture_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_modify_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_modify_livre_facture_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_create_livre_facture_enabled(bool p_enabled)
{
  m_livre_facture_widget->set_create_livre_facture_enabled(p_enabled);
}

// Interactions with non attributed facture information
//-------------------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_date(const std::string & p_date)
{
  m_livre_facture_widget->set_non_attributed_facture_date(p_date);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs)
{
  m_livre_facture_widget->set_allowed_facture_references(p_remaining_refs);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reference(uint32_t p_ref)
{
   m_livre_facture_widget->set_facture_reference(p_ref);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids)
{
  m_livre_facture_widget->set_allowed_livre_ids(p_livre_ids);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_status_list(const std::vector<facture_status> & p_status_list)
{
  m_livre_facture_widget->set_status_list(p_status_list);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_status(uint32_t p_id)
{
  m_livre_facture_widget->set_status(p_id);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reason_list(const std::vector<facture_reason> & p_reason_list)
{
  m_livre_facture_widget->set_reason_list(p_reason_list);
}

//------------------------------------------------------------------------------
void main_window::set_non_attributed_facture_reason(uint32_t p_id)
{
  m_livre_facture_widget->set_reason(p_id);
}

//------------------------------------------------------------------------------
const std::string main_window::get_non_attributed_facture_date(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_date();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_non_attributed_facture_livre_facture_id(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_livre_facture_id();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_non_attributed_facture_reference(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_reference();
}

//------------------------------------------------------------------------------
const facture_status * main_window::get_non_attributed_facture_status(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_status();
}

//------------------------------------------------------------------------------
const facture_reason * main_window::get_non_attributed_facture_reason(void)const
{
  return m_livre_facture_widget->get_non_attributed_facture_reason();
}

//------------------------------------------------------------------------------
void main_window::clear_non_attributed_facture_date(void)
{
  m_livre_facture_widget->clear_non_attributed_facture_date();
}

//------------------------------------------------------------------------------
void main_window::enable_non_attributed_facture_fields(bool p_enable)
{
  m_livre_facture_widget->enable_non_attributed_facture_fields(p_enable);
}

//------------------------------------------------------------------------------
bool main_window::is_non_attributed_facture_date_complete(void)const
{
  return m_livre_facture_widget->is_non_attributed_facture_date_complete();
}

//------------------------------------------------------------------------------
bool main_window::is_non_attributed_facture_date_empty(void)const
{
  return m_livre_facture_widget->is_non_attributed_facture_date_empty();
}

// Interactions with non attributed facture list
//-----------------------------------------------
//------------------------------------------------------------------------------
void main_window::refresh_list_facture_of_livre_facture(std::vector<search_facture_client_item> & p_list)
{
  m_livre_facture_widget->refresh_list_facture_of_livre_facture(p_list);
}

//------------------------------------------------------------------------------
bool main_window::is_list_facture_of_livre_facture_selection_empty(void)const
{
  return m_livre_facture_widget->is_list_facture_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_list_facture_of_livre_facture_selected_id(void)const
{
  return m_livre_facture_widget->get_list_facture_selected_id();
}


// Interactions with non attributed facture buttons
//---------------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_facture_creation_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_creation_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_facture_deletion_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_deletion_enabled(p_enabled);
}

//------------------------------------------------------------------------------
void main_window::set_facture_modification_for_selected_livre_enabled( bool p_enabled)
{
  m_livre_facture_widget->set_facture_modification_enabled(p_enabled);
}

// Interactions with facture status information
//---------------------------------------------
void main_window::clear_facture_status_information(void)
{
  m_facture_status_widget->clear_facture_status_information();
}

//---------------------------------------------
void main_window::set_facture_status_name(const std::string & p_name)
{
  m_facture_status_widget->set_facture_status_name(p_name);
}
 
//---------------------------------------------
const std::string main_window::get_facture_status_name(void)const
{
  return m_facture_status_widget->get_facture_status_name();
}

// Interactions with facture status list
//--------------------------------------
//------------------------------------------------------------------------------
bool main_window::is_facture_status_selection_empty(void)const
{
  return m_facture_status_widget->is_facture_status_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_facture_status_id(void)const
{
  return m_facture_status_widget->get_selected_facture_status_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_facture_status_list(std::vector<facture_status> & p_list)
{
  m_facture_status_widget->refresh_facture_status_list(p_list);
}

//------------------------------------------------------------------------------
void  main_window::set_facture_status_list_enabled(bool p_enable)
{
  m_facture_status_widget->set_facture_status_list_enabled(p_enable);
}

// Interactions with facture status actions
//------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_create_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_create_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_delete_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_delete_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_status_enabled(bool p_enable)
{
  m_facture_status_widget->set_modify_facture_status_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_status_action_name(const std::string & p_name)
{
  m_facture_status_widget->set_modify_facture_status_action_name(p_name);
}

// Interactions with facture reason information
//---------------------------------------------
void main_window::clear_facture_reason_information(void)
{
  m_facture_reason_widget->clear_facture_reason_information();
}

//---------------------------------------------
void main_window::set_facture_reason_name(const std::string & p_name)
{
  m_facture_reason_widget->set_facture_reason_name(p_name);
}
 
//---------------------------------------------
const std::string main_window::get_facture_reason_name(void)const
{
  return m_facture_reason_widget->get_facture_reason_name();
}

// Interactions with facture reason list
//--------------------------------------
//------------------------------------------------------------------------------
bool main_window::is_facture_reason_selection_empty(void)const
{
  return m_facture_reason_widget->is_facture_reason_selection_empty();
}

//------------------------------------------------------------------------------
uint32_t main_window::get_selected_facture_reason_id(void)const
{
  return m_facture_reason_widget->get_selected_facture_reason_id();
}

//------------------------------------------------------------------------------
void main_window::refresh_facture_reason_list(std::vector<facture_reason> & p_list)
{
  m_facture_reason_widget->refresh_facture_reason_list(p_list);
}

//------------------------------------------------------------------------------
void  main_window::set_facture_reason_list_enabled(bool p_enable)
{
  m_facture_reason_widget->set_facture_reason_list_enabled(p_enable);
}

// Interactions with facture reason actions
//------------------------------------------
//------------------------------------------------------------------------------
void main_window::set_create_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_create_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_delete_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_delete_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_reason_enabled(bool p_enable)
{
  m_facture_reason_widget->set_modify_facture_reason_enabled(p_enable);
}

//------------------------------------------------------------------------------
void main_window::set_modify_facture_reason_action_name(const std::string & p_name)
{
  m_facture_reason_widget->set_modify_facture_reason_action_name(p_name);
}



//------------------------------------------------------------------------------
void main_window::treat_test_event(void)
{
  test::test();
}

//------------------------------------------------------------------------------
void main_window::treat_import_event(void)
{
  cout << "QtEvent::Import" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
						     tr("Open Database"), ".",
						     tr("SQL database files (*.sql)"));
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

      setWindowTitle(l_file_name);

      manage_features(true);
    }
}


//------------------------------------------------------------------------------
void main_window::treat_open_db_event(void)
{
  cout << "QtEvent::Open" << endl ;
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
      setWindowTitle(l_file_name);
      manage_features(true);
    }
}

//------------------------------------------------------------------------------
void main_window::exit(void)
{
  cout << "QtEvent::Exit" << endl ;
  close();
}

//------------------------------------------------------------------------------
void main_window::treat_save_event(void)
{
  cout << "QtEvent::Save" << endl ;
  m_fichier_client.save();
}

//------------------------------------------------------------------------------
void main_window::treat_save_as_event(void)
{
  cout << "QtEvent::Save as" << endl ;
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
      setWindowTitle(l_file_name);
    }
}

//------------------------------------------------------------------------------
void main_window::treat_close_db_event(void)
{
  cout << "QtEvent::Close" << endl ;
  bool l_close = true;
  if(m_fichier_client.need_save())
    {
      string l_question = "Database has non saved modification\nAre you sure you want to close it ?";
      int l_result = QMessageBox::question(this, tr("Close"),
					   tr(l_question.c_str()),
					   QMessageBox::Yes | QMessageBox::Default,
					   QMessageBox::No);
      if (l_result != QMessageBox::Yes)
	{
	  l_close = false;
	}
    }
  if(l_close)
    {
      m_open_file_action->setEnabled(true);
      m_save_action->setEnabled(false);
      m_save_as_action->setEnabled(false);
      m_close_action->setEnabled(false);
      manage_features(false);
      m_fichier_client.close_db();
      setWindowTitle(tr("Fichier client"));
    }
}

//------------------------------------------------------------------------------
void main_window::closeEvent(QCloseEvent *event)
{
  string l_question("Are you sure want to quit ?");
  if(m_fichier_client.need_save())
    {
      l_question += "\nDatabase has non saved modification\n";
    }
  int l_result = QMessageBox::question(this, tr("Quit"),
				       tr(l_question.c_str()),
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

//------------------------------------------------------------------------------
void main_window::create_actions(void)
{
  m_import_file_action = new QAction(tr("&Import"),this);
  m_import_file_action->setShortcut(tr("Ctrl+I"));
  m_import_file_action->setStatusTip(tr("Import a file from MySql")); 
  connect(m_import_file_action,SIGNAL(triggered()),this,SLOT(treat_import_event()));

  m_open_file_action = new QAction(tr("&Open"),this);
  m_open_file_action->setShortcut(tr("Ctrl+O"));
  m_open_file_action->setStatusTip(tr("Open a file")); 
  connect(m_open_file_action,SIGNAL(triggered()),this,SLOT(treat_open_db_event()));

  m_save_action = new QAction(tr("&Save"),this);
  m_save_action->setShortcut(tr("Ctrl+S"));
  m_save_action->setStatusTip(tr("Save current file")); 
  connect(m_save_action,SIGNAL(triggered()),this,SLOT(treat_save_event()));

  m_save_as_action = new QAction(tr("&Save As"),this);
  m_save_as_action->setShortcut(tr("Ctrl+E"));
  m_save_as_action->setStatusTip(tr("Save a file with a new name")); 
  connect(m_save_as_action,SIGNAL(triggered()),this,SLOT(treat_save_as_event()));

  m_close_action = new QAction(tr("&Close"),this);
  m_close_action->setShortcut(tr("Ctrl+C"));
  m_close_action->setStatusTip(tr("Close current file")); 
  connect(m_close_action,SIGNAL(triggered()),this,SLOT(treat_close_db_event()));

  m_test_action = new QAction(tr("&Test"),this);
  m_test_action->setShortcut(tr("Ctrl+T"));
  m_test_action->setStatusTip(tr("Launch test actions")); 
  connect(m_test_action,SIGNAL(triggered()),this,SLOT(treat_test_event()));

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

//EOF
