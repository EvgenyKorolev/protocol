#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T13:41:43
#
#-------------------------------------------------
CONFIG += c++14
QT += core gui xml sql webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = protocol
TEMPLATE = app


SOURCES += src/address.cpp \
    src/app_data_model.cpp \
    src/app_data_view.cpp \
    src/app_editor.cpp \
    src/apparaturs.cpp \
    src/cp.cpp \
    src/details.cpp \
    src/directory_app.cpp \
    src/editor_address.cpp \
    src/editor_cp.cpp \
    src/editor_klient.cpp \
    src/editor_ktp.cpp \
    src/editor_laboratory.cpp \
    src/editor_order.cpp \
    src/editor_worker.cpp \
    src/fab_app.cpp \
    src/fab_item.cpp \
    src/fab_klient.cpp \
    src/fab_obj.cpp \
    src/fab_order.cpp \
    src/int_editor.cpp \
    src/klient.cpp \
    src/ktp.cpp \
    src/laboratory.cpp \
    src/logger.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/my_date_edit.cpp \
    src/my_function.cpp \
    src/my_list_model.cpp \
    src/my_list_view.cpp \
    src/my_time_model.cpp \
    src/my_time_view.cpp \
    src/mytreeview.cpp \
    src/obj.cpp \
    src/open_klient.cpp \
    src/order.cpp \
    src/pair_editor.cpp \
    src/pair_time_editor.cpp \
    src/save_klient.cpp \
    src/string_edit.cpp \
    src/time_editor.cpp \
    src/transformator.cpp \
    src/treeitem.cpp \
    src/treemodel.cpp \
    src/ver_data_model.cpp \
    src/ver_data_view.cpp \
    src/ver_editor.cpp \
    src/worker.cpp \
    src/workers_data.cpp \
    src/workers_view.cpp \
    src/yes_no.cpp \
    src/fstring_edit.cpp \
    src/editor_trans.cpp \
    src/direct_app_listing.cpp \
    src/direct_app_model.cpp \
    src/direct_app_view.cpp \
    src/filter_maker.cpp \
    src/app_in_direct.cpp \
    src/app_in_view.cpp \
    src/const_data_model.cpp \
    src/const_data_view.cpp \
    src/const_data_listing.cpp \
    src/const_loader.cpp \
    src/const_obj.cpp \
    src/const_data_editor.cpp \
    src/type_const_loader.cpp \
    src/type_obj.cpp \
    src/type_data_model.cpp \
    src/type_data_view.cpp \
    src/type_data_listing.cpp \
    src/type_data_editor.cpp \
    src/close_class.cpp \
    src/protocol.cpp \
    src/edit_html.cpp \
    src/var_adapter.cpp \
    src/const_adapter.cpp \
    src/type_adapter.cpp \
    src/protocol_constructor.cpp \
    src/p_types_view.cpp \
    src/p_types_model.cpp \
    src/pair_plus_editor.cpp \
    src/p_type_select.cpp \
    src/p_tyo_select_view.cpp \
    src/type_in_direct.cpp \
    src/type_in_view.cpp \
    src/lab_adapter.cpp \

HEADERS  += src/address.h \
    src/app_data_model.h \
    src/app_data_view.h \
    src/app_editor.h \
    src/apparaturs.h \
    src/cp.h \
    src/details.h \
    src/directory_app.h \
    src/editor_address.h \
    src/editor_cp.h \
    src/editor_klient.h \
    src/editor_ktp.h \
    src/editor_laboratory.h \
    src/editor_order.h \
    src/editor_worker.h \
    src/fab_app.h \
    src/fab_item.h \
    src/fab_klient.h \
    src/fab_obj.h \
    src/fab_order.h \
    src/int_editor.h \
    src/klient.h \
    src/ktp.h \
    src/laboratory.h \
    src/logger.h \
    src/mainwindow.h \
    src/my_date_edit.h \
    src/my_function.h \
    src/my_list_model.h \
    src/my_list_view.h \
    src/my_time_model.h \
    src/my_time_view.h \
    src/mytreeview.h \
    src/obj.h \
    src/open_klient.h \
    src/order.h \
    src/pair_editor.h \
    src/pair_time_editor.h \
    src/pair_type.h \
    src/ppair_type.h \
    src/save_klient.h \
    src/string_edit.h \
    src/time_editor.h \
    src/transformator.h \
    src/treeitem.h \
    src/treemodel.h \
    src/ver_data_model.h \
    src/ver_data_view.h \
    src/ver_editor.h \
    src/worker.h \
    src/workers_data.h \
    src/workers_view.h \
    src/yes_no.h \
    src/fstring_edit.h \
    src/editor_trans.h \
    src/direct_app_listing.h \
    src/direct_app_model.h \
    src/direct_app_view.h \
    src/filter_maker.h \
    src/app_in_direct.h \
    src/app_in_view.h \
    src/const_data_model.h \
    src/const_data_view.h \
    src/const_data_listing.h \
    src/const_loader.h \
    src/const_obj.h \
    src/const_data_editor.h \
    src/type_const_loader.h \
    src/type_obj.h \
    src/type_data_model.h \
    src/type_data_view.h \
    src/type_data_listing.h \
    src/type_data_editor.h \
    src/close_class.h \
    src/protocol.h \
    src/edit_html.h \
    src/var_adapter.h \
    src/const_adapter.h \
    src/type_adapter.h \
    src/protocol_constructor.h \
    src/p_types_view.h \
    src/p_types_model.h \
    src/pair_plus_editor.h \
    src/p_type_select.h \
    src/p_tyo_select_view.h \
    src/type_in_direct.h \
    src/type_in_view.h \
    src/lab_adapter.h \

RESOURCES += \
    icons.qrc \
    data.qrc

DISTFILES += \
    data/app.db3 \
    images/Klogo.png \
    images/KlogoM.png \
    images/KlogoS.png \
    images/st0.png \
    data/lab.dat \
    data/prt.log \
