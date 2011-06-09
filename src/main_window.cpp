#include "main_window.h"
#include "test.h"
#include "my_date_widget.h"
#include "search_widget.h"
#include "livre_facture_widget.h"

#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMenuBar>

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
  m_livre_facture_widget(NULL)
{
  setWindowTitle(tr("Fichier client"));
  create_actions();
  create_menus();
  create_status_bar();

  QTabWidget * m_tab_widget = new QTabWidget();

  m_livre_facture_widget = new livre_facture_widget(m_fichier_client);

  // Search widget
  m_search_widget = new search_widget(m_fichier_client);


  m_tab_widget->addTab(m_search_widget,tr("Search"));
  m_tab_widget->addTab(m_livre_facture_widget,tr("Livre facture"));

  setCentralWidget(m_tab_widget);

  manage_features(false);

  setMinimumSize(160, 160);
  resize(800, 600);
}

//------------------------------------------------------------------------------
void main_window::manage_features(bool p_enable)
{
  m_search_widget->set_enable(p_enable);
  m_livre_facture_widget->set_enable(p_enable);
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

      setWindowTitle(l_file_name);

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
      setWindowTitle(l_file_name);
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
      setWindowTitle(l_file_name);
    }
}

//------------------------------------------------------------------------------
void main_window::close_db(void)
{
  cout << "Close" << endl ;
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
//EOF
