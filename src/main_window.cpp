#include "main_window.h"
#include <iostream>
using namespace std;

main_window::main_window(void):
  m_open_file_action(NULL),
  m_exit_action(NULL),
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
  //  connect(m_client_list_table,SIGNAL(cellClicked (int, int)),this, SLOT(client_selected(int)));

  setCentralWidget(l_frame);

  setMinimumSize(160, 160);
  resize(480, 320);
}

void main_window::create_actions(void)
{
  m_open_file_action = new QAction(tr("&Import"),this);
  m_open_file_action->setShortcut(tr("Ctrl+I"));
  m_open_file_action->setStatusTip(tr("Import a file from MySql")); 
  connect(m_open_file_action,SIGNAL(triggered()),this,SLOT(open()));

  m_exit_action = new QAction(tr("&Quit"),this);
  m_exit_action->setShortcut(tr("Ctrl+Q"));
  m_exit_action->setStatusTip(tr("Quit the application")); 
  connect(m_exit_action,SIGNAL(triggered()),this,SLOT(exit()));
}

void main_window::create_menus(void)
{
  m_file_menu = menuBar()->addMenu(tr("&File"));
  m_file_menu->addAction(m_open_file_action);
  m_file_menu->addAction(m_exit_action);
}

void main_window::create_status_bar(void)
{
  m_status_label = new QLabel("Status bar");
  statusBar()->addWidget(m_status_label);
}

void main_window::open(void)
{
  cout << "Open a file" << endl ;
  QString l_file_name = QFileDialog::getOpenFileName(this,
                                   tr("Open Database"), ".",
                                   tr("Spreadsheet files (*.sql)"));
  string l_file_name_std = l_file_name.toStdString();
  cout << "File to open is \"" << l_file_name_std << "\"" << endl ;
  if(l_file_name != "")
    {
      m_open_file_action->setEnabled(false);
      m_fichier_client.import_external_sql(l_file_name_std);
      QMessageBox::information (this,"Import Status","File successfully imported", QMessageBox::Ok,QMessageBox::Ok);
    }
}

void main_window::exit(void)
{
  cout << "Exit" << endl ;
  close();
}

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

void main_window::client_selected(int p_row)
{
  cout << "Row selected " << p_row << endl ;
  uint32_t l_client_id = m_client_list_table->get_selected_client_id(p_row);
  cout << "Id of selected client " << l_client_id << endl;
  vector<search_achat_item> l_list_achat;
  m_fichier_client.get_achat_by_client_id(l_client_id,l_list_achat);
  m_achat_list_table->update(l_list_achat);  
}

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
