/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file drawing_register_font.h
 *
 * @brief This file declares the functions related to the font manager in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

/**
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides the 2D drawing capability.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 11
 * @version 1.0
 */
#ifndef C_INCLUDE_DRAWING_REGISTER_FONT_H
#define C_INCLUDE_DRAWING_REGISTER_FONT_H
#include "drawing_text_declaration.h"
#include "drawing_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于在字体管理器中注册自定义字体，支持的字体文件格式包含：ttf、otf。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向{@link OH_Drawing_FontCollection}对象的指针。
 * @param fontFamily 指需要注册的字体的字体名称。
 * @param familySrc 指需要注册的字体文件的路径。
 * @return 返回错误代码，0为成功，1为文件不存在，2为打开文件失败，3为读取文件失败，4为寻找文件失败，5为获取大小失败，9文件损坏。
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFont(OH_Drawing_FontCollection* fontCollection, const char* fontFamily,
    const char* familySrc);

/**
 * @brief 用于在字体管理器中注册字体缓冲区。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向{@link OH_Drawing_FontCollection}对象的指针。
 * @param fontFamily 指需要注册的字体的字体名称。
 * @param fontBuffer 指需要注册的字体文件的缓冲区。
 * @param length 指需要注册的字体文件的长度。
 * @return 返回错误代码，0为成功，6为缓冲区大小为零，7为字体集合为空，9为文件损坏。
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_RegisterFontBuffer(OH_Drawing_FontCollection* fontCollection, const char* fontFamily,
    uint8_t* fontBuffer, size_t length);

/**
 * @brief 使用ttc/otc文件注册自定义字体。
 *
 * @param fontCollection 指向{@link OH_Drawing_FontCollection}对象的指针。
 * @param fontFamily 需要注册的字体的字体名称。
 * @param familySrc 需要注册的字体文件的路径。
 * @param index 字体在ttc/otc文件中的索引，非ttc/otc格式文件需设置为0。
 * @return 函数执行结果。0为成功，1为文件不存在，2为打开文件失败，3为读取文件失败，4为寻找文件失败，5为获取大小失败，8为fontCollection为空，9为文件损坏。
 * @since 23
 */
uint32_t OH_Drawing_RegisterFontByIndex(OH_Drawing_FontCollection* fontCollection,
    const char* fontFamily, const char* familySrc, uint32_t index);

/**
 * @brief 使用ttc/otc文件字节流注册字体。
 *
 * @param fontCollection 指向{@link OH_Drawing_FontCollection}对象的指针。
 * @param fontFamily 需要注册的字体的字体名称。
 * @param fontBuffer 需要注册的字体文件的字节流数据。
 * @param length 字节流数据长度
 * @param index 字体在ttc/otc文件中的索引，非ttc/otc格式文件需设置为0。
 * @return 函数执行结果。0为成功，6为字节流指针为空，7为字节流长度为0，8为fontCollection为空，9为文件损坏。
 * @since 23
 */
uint32_t OH_Drawing_RegisterFontBufferByIndex(OH_Drawing_FontCollection* fontCollection,
    const char* fontFamily, uint8_t* fontBuffer, size_t length, uint32_t index);

/**
 * @brief 通过字体家族名称取消注册自定义字体。取消注册当前正在使用的字体可能导致文本渲染异常，包括乱码或字形缺失。所有使用被取消注册的字体家族名称的排版对象都应该被销毁重建。
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param fontCollection 指向{@link OH_Drawing_FontCollection}对象的指针。
 * @param fontFamily 需要取消注册的字体家族名称。
 * @return 返回执行结果状态码，0为成功，8为入参不合法，1为取消注册失败。
 * @since 20
 */
uint32_t OH_Drawing_UnregisterFont(OH_Drawing_FontCollection* fontCollection, const char* fontFamily);

/**
 * @brief 检查系统是否支持指定路径的字体格式。
 *
 * @param path 字体文件的绝对路径。
 * @return 如果支持该字体则返回true；否则返回false。
 * @since 23
 */
bool OH_Drawing_IsFontSupportedFromPath(const char* path);

/**
 * @brief 检查系统是否支持缓冲区中指定的字体格式。
 *
 * @param data 包含字体数据的内存缓冲区的指针。
 * @param dataLength 字体数据的大小（以字节为单位）。
 * @return 如果支持该字体则返回true；否则返回false。
 * @since 23
 */
bool OH_Drawing_IsFontSupportedFromBuffer(uint8_t* data, size_t dataLength);
#ifdef __cplusplus
}
#endif

/** @} */
#endif