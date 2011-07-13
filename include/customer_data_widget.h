#ifndef _CUSTOMER_DATA_WIDGET_H_
#define _CUSTOMER_DATA_WIDGET_H_

#include <QWidget>
#include "ville.h"

class fichier_client;

class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class base_facture_widget;
class facture_list_table;
class achat_list_table;

class customer_data_widget: public QWidget
{
  Q_OBJECT
    public:
   customer_data_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

   // Interactions with customer identity information
   void set_name(const std::string & p_name);
   const std::string get_name(void)const;
   void set_first_name(const std::string & p_first_name);
   const std::string get_first_name(void)const;
   void set_phone(const std::string & p_phone);
   const std::string get_phone(void)const;
   bool is_phone_empty(void)const;
   bool is_phone_complete(void)const;
   void set_address(const std::string & p_address);
   const std::string get_address(void)const;
   void set_postal_code(const std::string & p_postal_code);
   const std::string get_postal_code(void)const;
   void set_city_list(const std::vector<ville> & p_list);
   const ville * get_city(void)const;
   void set_identity_fields_enabled(bool p_enabled);
   void set_create_customer_enabled(bool p_enabled);
   void set_modify_customer_enabled(bool p_enabled);
   void set_delete_customer_enabled(bool p_enabled);

   // Interactions with customer bill information
   void set_bill_fields_enabled(bool p_enabled);
   void set_bill_list_enabled(bool p_enabled);
   void set_bill_creation_enabled(bool p_enabled);
   void set_bill_modification_enabled(bool p_enabled);
   void set_bill_deletion_enabled(bool p_enabled);
   
   // Interactions with customer purchase information
   void set_purchase_fields_enabled(bool p_enabled);
   void set_purchase_list_enabled(bool p_enabled);
   void set_purchase_creation_enabled(bool p_enabled);
   void set_purchase_modification_enabled(bool p_enabled);
   void set_purchase_deletion_enabled(bool p_enabled);

   private slots:
   void treat_postal_code_modification_event(void);
   void treat_city_selection_event(void);
   void treat_identity_content_modification_event(void);
   void treat_create_customer_event(void);
   void treat_modify_customer_event(void);
   void treat_delete_customer_event(void);
   
 private:
   QLineEdit * m_name_field;
   QLineEdit * m_first_name_field;
   QLineEdit * m_phone_field;
   QLineEdit * m_address_field;
   QLineEdit * m_postal_code_field;
   QComboBox * m_city_field;
   QPushButton * m_create_customer_button;
   QPushButton * m_modify_customer_button;
   QPushButton * m_delete_customer_button;
   base_facture_widget * m_bill_widget;
   facture_list_table *m_bill_list_table;
   QPushButton * m_create_bill_button;
   QPushButton * m_modify_bill_button;
   QPushButton * m_delete_bill_button;
   QComboBox * m_brand_field;
   QComboBox * m_type_field;
   QLineEdit * m_purchase_reference_field;
   QLineEdit * m_euro_price_field;
   QLineEdit * m_franc_price_field;
   QCheckBox * m_warranty_field;
   achat_list_table *m_purchase_list_table;
   QPushButton * m_create_purchase_button;
   QPushButton * m_modify_purchase_button;
   QPushButton * m_delete_purchase_button;
   std::vector<ville> m_cities;
   fichier_client & m_fichier_client;
};
#endif
