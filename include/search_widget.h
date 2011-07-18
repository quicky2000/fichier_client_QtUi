#ifndef _SEARCH_WIDGET_H_
#define _SEARCH_WIDGET_H_

#include <QWidget>
#include "search_client_item.h"
#include "search_achat_item.h"
#include "search_facture_item.h"

class QLineEdit;
class QPushButton;
class fichier_client;
class client_list_table;
class achat_list_table;
class facture_list_table;

class search_widget : public QWidget
 {
     Q_OBJECT

 public:
   search_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

   void set_enable(bool p_enable);

   // Interactions with customer search criteria information
   const std::string get_customer_name(void)const;
   const std::string get_customer_first_name(void)const;
   const std::string get_customer_address(void)const;
   const std::string get_customer_city(void)const;
   
   void update_customer_list(const std::vector<search_client_item> & p_list);
   void update_customer_list_achat(const std::vector<search_achat_item> & p_list);
   void update_customer_list_facture(const std::vector<search_facture_item> & p_list);
   void set_add_customer_enabled(bool p_enabled);
   void set_modify_customer_enabled(bool p_enabled);
   void set_delete_customer_enabled(bool p_enabled);
   uint32_t get_selected_customer(void)const;

 private slots:
     void treat_criteria_modification_event(void);
     void treat_customer_selected_event(int row);
     void treat_customer_selection_changed_event(void);
     void treat_add_customer_event(void);
     void treat_modify_customer_event(void);
     void treat_delete_customer_event(void);
 private:
     QLineEdit * m_name_field;
     QLineEdit * m_first_name_field;
     QLineEdit * m_address_field;
     QLineEdit * m_city_field;
     client_list_table *m_client_list_table;
     QPushButton * m_add_customer_button;
     QPushButton * m_modify_customer_button;
     QPushButton * m_delete_customer_button;
     achat_list_table *m_achat_list_table;
     facture_list_table *m_facture_list_table;
     fichier_client & m_fichier_client;
 };

#endif
