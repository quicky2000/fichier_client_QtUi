#ifndef _LIVRE_FACTURE_WIDGET_H_
#define _LIVRE_FACTURE_WIDGET_H_

#include <QWidget>
#include <stdint.h>
#include "facture_status.h"
#include "search_facture_client_item.h"

class QPushButton;
class QLineEdit;

class fichier_client;
class livre_facture_table;
class livre_facture;
class my_date_widget;
class base_facture_widget;
class facture_client_list_table;

class livre_facture_widget : public QWidget
 {
     Q_OBJECT

 public:
   livre_facture_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
   void set_enable(bool p_enable);

   // Interactions with livre facture fields
   void clear_livre_facture_information(void);
   void set_livre_facture_start_date(const std::string & p_date);
   void set_livre_facture_end_date(const std::string & p_date);
   void set_livre_facture_id(const std::string & p_id);
   const std::string get_livre_facture_start_date(void)const;
   bool is_livre_facture_start_date_complete(void)const;
   const std::string get_livre_facture_end_date(void)const;
   bool is_livre_facture_end_date_complete(void)const;
   const std::string get_livre_facture_id(void)const;

   // Interactions with livre facture list
   bool is_livre_facture_selection_empty(void)const;
   uint32_t get_selected_livre_facture_id(void)const;
   void refresh_livre_facture_list(std::vector<livre_facture> & p_list);

   // Interactions with livre facture buttons
   void set_delete_livre_facture_enabled(bool p_enabled);
   void set_modify_livre_facture_enabled(bool p_enabled);
   void set_create_livre_facture_enabled(bool p_enabled);

   // Interactions with non attributed facture fields
   void set_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs);
   void set_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
   void set_status_list(const std::vector<facture_status> & p_status_list);
   const std::string get_non_attributed_facture_date(void)const;
   uint32_t get_non_attributed_facture_livre_facture_id(void)const;
   uint32_t get_non_attributed_facture_reference(void)const;
   const facture_status * get_non_attributed_facture_status(void)const;
   void clear_non_attributed_facture_date(void);
   void enable_non_attributed_facture_fields(bool p_enable);
   bool is_non_attributed_facture_date_complete(void)const;
   bool is_non_attributed_facture_date_empty(void)const;

   // Interactions with non attributed facture list
   void refresh_list_facture_of_livre_facture(std::vector<search_facture_client_item> & p_list);

   // Interaction with non attributed facture buttons
   void set_facture_creation_enabled(bool p_enabled);

 private slots:
   //Livre facture fields events
   void treat_livre_facture_id_modif_event(void);
   void treat_livre_facture_content_modif_event(void);
   // Livre facture button events
   void treat_create_livre_facture_event(void);
   void treat_delete_livre_facture_event(void);
   void treat_modify_livre_facture_event(void);
   // Livre facture table events
   void treat_livre_facture_selected_event(int row);
   void treat_livre_facture_selection_changed_event(void);
   // Non attributed facture button events
   void treat_create_facture_event(void);
   void treat_delete_facture_event(void);
   void treat_modify_facture_event(void);
   // Non attributed facture table events
   void treat_facture_selected_event(int row);
   void treat_facture_selection_changed_event(void);
   // Non attributed facture fields events
   void treat_non_attributed_facture_date_entered_event(void);
   void treat_non_attributed_facture_ref_selected_event(void);
   void treat_non_attributed_facture_status_selected_event(void);
   void treat_non_attributed_facture_livre_facture_selected_event(void);
 private:
     QPushButton * m_create_livre_facture_button;
     QPushButton * m_delete_livre_facture_button;
     QPushButton * m_modify_livre_facture_button;
     QLineEdit * m_livre_id_field;
     my_date_widget * m_start_date_field;
     my_date_widget * m_end_date_field;
     livre_facture_table *m_livre_facture_table;
     // Facture related part
     QPushButton * m_create_facture_button;
     QPushButton * m_delete_facture_button;
     QPushButton * m_modify_facture_button;
     base_facture_widget * m_base_facture_widget;
     facture_client_list_table *m_facture_client_list_table;
     fichier_client & m_fichier_client;
 };

#endif
