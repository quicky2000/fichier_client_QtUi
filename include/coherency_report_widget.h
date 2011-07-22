#ifndef _COHERENCY_REPORT_WIDGET_H_
#define _COHERENCY_REPORT_WIDGET_H_

#include <QWidget>
#include "coherency_report_item.h"

class fichier_client;
class QLineEdit;
class QPushButton;
class list_table_coherency_report;

class coherency_report_widget:public QWidget
{
  Q_OBJECT
 public:
  coherency_report_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
  void set_enable(bool p_enabled);

  // Interactions with coherency actions
  void set_launch_check_enabled(bool p_enable);

  // Interactions with coherency information
  void set_error_number(uint32_t p_nb);
  void set_error_list(std::vector<coherency_report_item> p_list);
  void set_warning_number(uint32_t p_nb);
  void set_warning_list(std::vector<coherency_report_item> p_list);

  private slots:

  // Coherency related events handler
  void treat_check_db_coherency_event(void);

 private:
  QPushButton * m_check_button;
  QLineEdit * m_nb_error_field;
  list_table_coherency_report * m_error_list;
  QLineEdit * m_nb_warning_field;
  list_table_coherency_report * m_warning_list;

  fichier_client & m_fichier_client;  
};

#endif /* _COHERENCY_REPORT_WIDGET_H_ */
//EOF
