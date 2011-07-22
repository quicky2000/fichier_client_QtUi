#include "coherency_report_widget.h"
#include "list_table_coherency_report.h"
#include "fichier_client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>

//------------------------------------------------------------------------------
coherency_report_widget::coherency_report_widget(fichier_client & p_fichier_client,QWidget * p_parent):
  QWidget(p_parent),
  m_check_button(NULL),
  m_nb_error_field(NULL),
  m_error_list(NULL),
  m_nb_warning_field(NULL),
  m_warning_list(NULL),
  m_fichier_client(p_fichier_client)
{
  QVBoxLayout * l_main_layout = new QVBoxLayout(this);

  m_check_button = new QPushButton("Verification");
  connect(m_check_button,SIGNAL(clicked()),this,SLOT(treat_check_db_coherency_event()));
  l_main_layout->addWidget(m_check_button);

  QGroupBox * l_error_group_box = new QGroupBox(tr("Erreurs"));

  QVBoxLayout * l_error_layout = new QVBoxLayout();

  QHBoxLayout * l_error_field_layout = new QHBoxLayout();
  l_error_field_layout->addWidget(new QLabel("Nombre d'erreurs :"));
  m_nb_error_field = new QLineEdit("");
  m_nb_error_field->setReadOnly(true);
  l_error_field_layout->addWidget(m_nb_error_field);

  l_error_layout->addLayout(l_error_field_layout);

  m_error_list = new list_table_coherency_report(this);
  l_error_layout->addWidget(m_error_list);
  
  l_error_group_box->setLayout(l_error_layout);
  l_main_layout->addWidget(l_error_group_box);


  QGroupBox * l_warning_group_box = new QGroupBox(tr("Warnings"));

  QVBoxLayout * l_warning_layout = new QVBoxLayout();

  QHBoxLayout * l_warning_field_layout = new QHBoxLayout();
  l_warning_field_layout->addWidget(new QLabel("Nombre de warning :"));
  m_nb_warning_field = new QLineEdit("");
  m_nb_warning_field->setReadOnly(true);
  l_warning_field_layout->addWidget(m_nb_warning_field);

  l_warning_layout->addLayout(l_warning_field_layout);

  m_warning_list = new list_table_coherency_report(this);
  l_warning_layout->addWidget(m_warning_list);

  l_warning_group_box->setLayout(l_warning_layout);
  l_main_layout->addWidget(l_warning_group_box);
}

//------------------------------------------------------------------------------
void coherency_report_widget::set_enable(bool p_enabled)
{
  m_check_button->setEnabled(p_enabled);
  m_nb_error_field->setEnabled(p_enabled);
  m_error_list->setEnabled(p_enabled);
  m_nb_warning_field->setEnabled(p_enabled);
  m_warning_list->setEnabled(p_enabled);
}

// Interactions with city actions
//------------------------------------------------------------------------------
void coherency_report_widget::set_launch_check_enabled(bool p_enable)
{
  m_check_button->setEnabled(p_enable);
}

// Interactions with coherency information
//------------------------------------------------------------------------------
void coherency_report_widget::set_error_number(uint32_t p_nb)
{
  QString l_nb_q;
  l_nb_q.setNum(p_nb);
  m_nb_error_field->setText(l_nb_q);
}

//------------------------------------------------------------------------------
void coherency_report_widget::set_error_list(std::vector<coherency_report_item> p_list)
{
  m_error_list->update(p_list);
}

//------------------------------------------------------------------------------
void coherency_report_widget::set_warning_number(uint32_t p_nb)
{
  QString l_nb_q;
  l_nb_q.setNum(p_nb);
  m_nb_warning_field->setText(l_nb_q);
}

//------------------------------------------------------------------------------
void coherency_report_widget::set_warning_list(std::vector<coherency_report_item> p_list)
{
  m_warning_list->update(p_list);
}

// Coherency related events handler
//------------------------------------------------------------------------------
void coherency_report_widget::treat_check_db_coherency_event(void)
{
  std::cout << "QtEvent::coherency_report_widget check button clicked" << std::endl;
  m_fichier_client.treat_check_db_coherency_event();
}


//EOF
