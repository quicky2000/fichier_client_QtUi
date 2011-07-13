#ifndef _CUSTOMER_DATA_WIDGET_H_
#define _CUSTOMER_DATA_WIDGET_H_

#include <QWidget>

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
   void set_address(const std::string & p_address);
   const std::string get_address(void)const;

 private:
   QLineEdit * m_name_field;
   QLineEdit * m_first_name_field;
   QLineEdit * m_phone_field;
   QLineEdit * m_address_field;
   QLineEdit * m_postal_code_field;
   QLineEdit * m_city_field;
   QPushButton * m_create_customer_button;
   QPushButton * m_modify_customer_button;
   QPushButton * m_delete_customer_button;
   base_facture_widget * m_facture_widget;
   facture_list_table *m_facture_list_table;
   QPushButton * m_create_facture_button;
   QPushButton * m_modify_facture_button;
   QPushButton * m_delete_facture_button;
   QComboBox * m_brand_field;
   QComboBox * m_type_field;
   QLineEdit * m_purchase_reference_field;
   QLineEdit * m_euro_price_field;
   QLineEdit * m_franc_price_field;
   QCheckBox * m_warranty_field;
   achat_list_table *m_achat_list_table;
   QPushButton * m_create_purchase_button;
   QPushButton * m_modify_purchase_button;
   QPushButton * m_delete_purchase_button;
   fichier_client & m_fichier_client;
};
#endif
