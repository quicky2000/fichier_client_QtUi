#ifndef _FACTURE_REASON_WIDGET_H_
#define _FACTURE_REASON_WIDGET_H_

#include <QWidget>
#include <stdint.h>

class QPushButton;
class QLineEdit;

class fichier_client;
class facture_reason_list_table;
class facture_reason;

class facture_reason_widget : public QWidget
 {
     Q_OBJECT

 public:
   facture_reason_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

  // Interactions with facture reason information
   void clear_facture_reason_information(void);
  void set_facture_reason_name(const std::string & p_name);  
  const std::string get_facture_reason_name(void)const;

  // Interactions with facture reason list
  bool is_facture_reason_selection_empty(void)const;
  uint32_t get_selected_facture_reason_id(void)const;
  void refresh_facture_reason_list(std::vector<facture_reason> & p_list);
  void set_facture_reason_list_enabled(bool p_enable);

  // Interactions with facture reason actions
  void set_create_facture_reason_enabled(bool p_enable);
  void set_delete_facture_reason_enabled(bool p_enable);
  void set_modify_facture_reason_enabled(bool p_enable);
  void set_modify_facture_reason_action_name(const std::string & p_name);

  void set_enable(bool p_enable);

 private slots:
   // Facture reason fields event
   void treat_criteria_modification_event(void);

   // Facture reason list events
   void treat_facture_reason_selected_event(int row);
   void treat_facture_reason_selection_changed_event(void);

   // Facture reason button events
   void treat_create_facture_reason_event(void);
   void treat_delete_facture_reason_event(void);
   void treat_modify_facture_reason_event(void);
 private:

   bool m_modif_pending;
   QPushButton * m_create_facture_reason_button;
   QPushButton * m_delete_facture_reason_button;
   QPushButton * m_modify_facture_reason_button;
   QLineEdit * m_reason_name_field;
   facture_reason_list_table *m_facture_reason_list_table;
   fichier_client & m_fichier_client;
 };

#endif
