#ifndef _FACTURE_STATUS_WIDGET_H_
#define _FACTURE_STATUS_WIDGET_H_

#include <QWidget>
#include <stdint.h>

class QPushButton;
class QLineEdit;

class fichier_client;
class facture_status_list_table;
class facture_status;

class facture_status_widget : public QWidget
 {
     Q_OBJECT

 public:
   facture_status_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

  // Interactions with facture status information
   void clear_facture_status_information(void);
  void set_facture_status_name(const std::string & p_name);  
  const std::string get_facture_status_name(void)const;

  // Interactions with facture status list
  bool is_facture_status_selection_empty(void)const;
  uint32_t get_selected_facture_status_id(void)const;
  void refresh_facture_status_list(std::vector<facture_status> & p_list);
  void set_facture_status_list_enabled(bool p_enable);

  // Interactions with facture status actions
  void set_create_facture_status_enabled(bool p_enable);
  void set_delete_facture_status_enabled(bool p_enable);
  void set_modify_facture_status_enabled(bool p_enable);
  void set_modify_facture_status_action_name(const std::string & p_name);

  void set_enable(bool p_enable);

 private slots:
   // Facture status fields event
   void treat_criteria_modification_event(void);

   // Facture status list events
   void treat_facture_status_selected_event(int row);
   void treat_facture_status_selection_changed_event(void);

   // Facture status button events
   void treat_create_facture_status_event(void);
   void treat_delete_facture_status_event(void);
   void treat_modify_facture_status_event(void);
 private:
   QPushButton * m_create_facture_status_button;
   QPushButton * m_delete_facture_status_button;
   QPushButton * m_modify_facture_status_button;
   QLineEdit * m_status_name_field;
   facture_status_list_table *m_facture_status_list_table;
   fichier_client & m_fichier_client;
 };

#endif
