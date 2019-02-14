#pragma once
#include "Save.h"

class NewSave
{
public:
    static void SaveToCSVBaseInfo(Save::BaseInfo* data, int length, int record);
    static void LoadFromCSVBaseInfo(Save::BaseInfo* data, int length, int record);
    // ����
    static void SaveToCSVItemList(ItemList* data, int length, int record);
    static void LoadFromCSVItemList(ItemList* data, int length, int record);
    // ����
    static void SaveToCSVRoleSave(const std::vector<Role>& data, int record);
    static void LoadFromCSVRoleSave(std::vector<Role>& data, int record);
    static void InsertRoleAt(std::vector<Role>& data, int idx);
    // ��Ʒ
    static void SaveToCSVItemSave(const std::vector<Item>& data, int record);
    static void LoadFromCSVItemSave(std::vector<Item>& data, int record);
    static void InsertItemAt(std::vector<Item>& data, int idx);
    // ����
    static void SaveToCSVSubMapInfoSave(const std::vector<SubMapInfo>& data, int record);
    static void LoadFromCSVSubMapInfoSave(std::vector<SubMapInfo>& data, int record);
    static void InsertSubMapInfoAt(std::vector<SubMapInfo>& data, int idx);
    // �书
    static void SaveToCSVMagicSave(const std::vector<Magic>& data, int record);
    static void LoadFromCSVMagicSave(std::vector<Magic>& data, int record);
    static void InsertMagicAt(std::vector<Magic>& data, int idx);
    // �̵�
    static void SaveToCSVShopSave(const std::vector<Shop>& data, int record);
    static void LoadFromCSVShopSave(std::vector<Shop>& data, int record);
    static void InsertShopAt(std::vector<Shop>& data, int idx);
};