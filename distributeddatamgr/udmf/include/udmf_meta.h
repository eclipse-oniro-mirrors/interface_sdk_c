/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup UDMF
 * @{
 *
 * @brief The Unified Data Management Framework(UDMF) aims to define various standards
 * for data across applications, devices, and platforms, providing a unified OpenHarmony
 * data language and standardized data access and reading paths.
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

/**
 * @file udmf_meta.h
 *
 * @brief Declares the uniform data type information.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

#ifndef UDMF_META_H
#define UDMF_META_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Generic type that represents all physical storage types. It is used to define physical properties of a type.
 * This type is uncategorized.
 *
 * @since 12
 */
#define UDMF_META_ENTITY "general.entity"

/**
 * @brief Generic type that represents all logical content types. It is used to define physical properties of a type.
 * This type is uncategorized.
 *
 * @since 12
 */
#define UDMF_META_OBJECT "general.object"

/**
 * @brief Generic composite content type. For example, a PDF file that contains text and image.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_COMPOSITE_OBJECT "general.composite-object"

/**
 * @brief Generic text type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_TEXT "general.text"

/**
 * @brief Text without specific encoding or identifier.
 * This type belongs to TEXT.
 *
 * @since 12
 */
#define UDMF_META_PLAIN_TEXT "general.plain-text"

/**
 * @brief HTML.
 * This type belongs to TEXT.
 *
 * @since 12
 */
#define UDMF_META_HTML "general.html"

/**
 * @brief Hyperlink.
 * This type belongs to TEXT.
 *
 * @since 12
 */
#define UDMF_META_HYPERLINK "general.hyperlink"

/**
 * @brief XML.
 * This type belongs to TEXT.
 *
 * @since 12
 */
#define UDMF_META_XML "general.xml"

/**
 * @brief Generic source code type.
 * This type belongs to PLAIN_TEXT.
 *
 * @since 12
 */
#define UDMF_META_SOURCE_CODE "general.source-code"

/**
 * @brief Source code in any scripting language.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_SCRIPT "general.script"

/**
 * @brief Shell script.
 * This type belongs to SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_SHELL_SCRIPT "general.shell-script"

/**
 * @brief C shell script.
 * This type belongs to SHELL_SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_CSH_SCRIPT "general.csh-script"

/**
 * @brief Perl script.
 * This type belongs to SHELL_SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_PERL_SCRIPT "general.perl-script"

/**
 * @brief PHP script.
 * This type belongs to SHELL_SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_PHP_SCRIPT "general.php-script"

/**
 * @brief Python script.
 * This type belongs to SHELL_SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_PYTHON_SCRIPT "general.python-script"

/**
 * @brief Ruby script.
 * This type belongs to SHELL_SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_RUBY_SCRIPT "general.ruby-script"

/**
 * @brief TypeScript source code.
 * This type belongs to SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_TYPE_SCRIPT "general.type-script"

/**
 * @brief JavaScript source code.
 * This type belongs to SCRIPT.
 *
 * @since 12
 */
#define UDMF_META_JAVA_SCRIPT "general.java-script"

/**
 * @brief Header file in C.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_C_HEADER "general.c-header"

/**
 * @brief Source code in C.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_C_SOURCE "general.c-source"

/**
 * @brief Header file in C++.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_HEADER "general.c-plus-plus-header"

/**
 * @brief Source code in C++.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_SOURCE "general.c-plus-plus-source"

/**
 * @brief Source code in Java.
 * This type belongs to SOURCE_CODE.
 *
 * @since 12
 */
#define UDMF_META_JAVA_SOURCE "general.java-source"

/**
 * @brief Generic eBook file format type.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_EBOOK "general.ebook"

/**
 * @brief Electronic publication (EPUB).
 * This type belongs to EBOOK.
 *
 * @since 12
 */
#define UDMF_META_EPUB "general.epub"

/**
 * @brief AZW.
 * This type belongs to EBOOK.
 *
 * @since 12
 */
#define UDMF_META_AZW "com.amazon.azw"

/**
 * @brief AZW3.
 * This type belongs to EBOOK.
 *
 * @since 12
 */
#define UDMF_META_AZW3 "com.amazon.azw3"

/**
 * @brief KFX.
 * This type belongs to EBOOK.
 *
 * @since 12
 */
#define UDMF_META_KFX "com.amazon.kfx"

/**
 * @brief MOBI.
 * This type belongs to EBOOK.
 *
 * @since 12
 */
#define UDMF_META_MOBI "com.amazon.mobi"

/**
 * @brief Generic media type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_MEDIA "general.media"

/**
 * @brief Image.
 * This type belongs to MEDIA.
 *
 * @since 12
 */
#define UDMF_META_IMAGE "general.image"

/**
 * @brief JPEG.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_JPEG "general.jpeg"

/**
 * @brief PNG.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_PNG "general.png"

/**
 * @brief Raw image.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_RAW_IMAGE "general.raw-image"

/**
 * @brief TIFF.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_TIFF "general.tiff"

/**
 * @brief BMP.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_BMP "com.microsoft.bmp"

/**
 * @brief Windows icon.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_ICO "com.microsoft.ico"

/**
 * @brief Adobe Photoshop image.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_PHOTOSHOP_IMAGE "com.adobe.photoshop-image"

/**
 * @brief Adobe Illustrator image (.ai).
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_AI_IMAGE "com.adobe.illustrator.ai-image"

/**
 * @brief Microsoft Word.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_WORD_DOC "com.microsoft.word.doc"

/**
 * @brief Microsoft Excel.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_EXCEL "com.microsoft.excel.xls"

/**
 * @brief Microsoft PowerPoint presentation format.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_PPT "com.microsoft.powerpoint.ppt"

/**
 * @brief PDF.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_PDF "com.adobe.pdf"

/**
 * @brief PostScript.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT "com.adobe.postscript"

/**
 * @brief Encapsulated PostScript.
 * This type belongs to POSTSCRIPT.
 *
 * @since 12
 */
#define UDMF_META_ENCAPSULATED_POSTSCRIPT "com.adobe.encapsulated-postscript"

/**
 * @brief Base video type.
 * This type belongs to MEDIA.
 *
 * @since 12
 */
#define UDMF_META_VIDEO "general.video"

/**
 * @brief AVI.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_AVI "general.avi"

/**
 * @brief MPEG-1 or MPEG-2.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_MPEG "general.mpeg"

/**
 * @brief MPEG-4.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_MPEG4 "general.mpeg-4"

/**
 * @brief 3GP (3GPP file format).
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP "general.3gpp"

/**
 * @brief 3G2 (3GPP2 file format).
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP2 "general.3gpp2"

/**
 * @brief Windows WM format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WM "com.microsoft.windows-media-wm"

/**
 * @brief Windows WMV format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMV "com.microsoft.windows-media-wmv"

/**
 * @brief Windows WMP format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMP "com.microsoft.windows-media-wmp"

/**
 * @brief Generic audio type.
 * This type belongs to MEDIA.
 *
 * @since 12
 */
#define UDMF_META_AUDIO "general.audio"

/**
 * @brief AAC.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_AAC "general.aac"

/**
 * @brief AIFF.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_AIFF "general.aiff"

/**
 * @brief ALAC.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_ALAC "general.alac"

/**
 * @brief FLAC.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_FLAC "general.flac"

/**
 * @brief MP3.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_MP3 "general.mp3"

/**
 * @brief OGG.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_OGG "general.ogg"

/**
 * @brief PCM.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_PCM "general.pcm"

/**
 * @brief Windows WMA format.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMA "com.microsoft.windows-media-wma"

/**
 * @brief Windows Waveform.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_WAVEFORM_AUDIO "com.microsoft.waveform-audio"

/**
 * @brief Windows WMX format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMX "com.microsoft.windows-media-wmx"

/**
 * @brief Windows WVX format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WVX "com.microsoft.windows-media-wvx"

/**
 * @brief Windows WAX format.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WAX "com.microsoft.windows-media-wax"

/**
 * @brief Generic file type.
 * This type belongs to ENTITY.
 *
 * @since 12
 */
#define UDMF_META_GENERAL_FILE "general.file"

/**
 * @brief Generic directory type.
 * This type belongs to ENTITY.
 *
 * @since 12
 */
#define UDMF_META_DIRECTORY "general.directory"

/**
 * @brief Generic folder type.
 * This type belongs to DIRECTORY.
 *
 * @since 12
 */
#define UDMF_META_FOLDER "general.folder"

/**
 * @brief Generic symbolic type.
 * This type belongs to ENTITY.
 *
 * @since 12
 */
#define UDMF_META_SYMLINK "general.symlink"

/**
 * @brief Generic archive file type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_ARCHIVE "general.archive"

/**
 * @brief BZ2.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_BZ2_ARCHIVE "general.bz2-archive"

/**
 * @brief Generic type of any file that can be mounted as a volume.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_DISK_IMAGE "general.disk-image"

/**
 * @brief TAR.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_TAR_ARCHIVE "general.tar-archive"

/**
 * @brief ZIP.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_ZIP_ARCHIVE "general.zip-archive"

/**
 * @brief JAR (Java archive).
 * This type belongs to ARCHIVE and EXECUTABLE.
 *
 * @since 12
 */
#define UDMF_META_JAVA_ARCHIVE "com.sun.java-archive"

/**
 * @brief GUN archive.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_GNU_TAR_ARCHIVE "org.gnu.gnu-tar-archive"

/**
 * @brief GZIP archive.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_ARCHIVE "org.gnu.gnu-zip-archive"

/**
 * @brief GZIP TAR.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_TAR_ARCHIVE "org.gnu.gnu-zip-tar-archive"

/**
 * @brief Generic calendar type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_CALENDAR "general.calendar"

/**
 * @brief Generic contact type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_CONTACT "general.contact"

/**
 * @brief Generic database file type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_DATABASE "general.database"

/**
 * @brief Generic message type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_MESSAGE "general.message"

/**
 * @brief Generic electronic business card type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_VCARD "general.vcard"

/**
 * @brief Generic navigation data type.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_NAVIGATION "general.navigation"

/**
 * @brief Location data.
 * This type belongs to NAVIGATION.
 *
 * @since 12
 */
#define UDMF_META_LOCATION "general.location"

/**
 * @brief Widget defined for the system.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_FORM "openharmony.form"

/**
 * @brief Home screen icon defined for the system.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_APP_ITEM "openharmony.app-item"

/**
 * @brief Pixel map defined for the system.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PIXEL_MAP "openharmony.pixel-map"

/**
 * @brief Atomic service type defined for the system.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_ATOMIC_SERVICE "openharmony.atomic-service"

/**
 * @brief Package (compressed folder) defined for the system.
 * This type belongs to DIRECTORY.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PACKAGE "openharmony.package"

/**
 * @brief Ability package defined for the system.
 * This type belongs to OPENHARMONY_PACKAGE.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HAP "openharmony.hap"

/**
 * @brief Synchronized Multimedia Integration Language (SMIL).
 * This type belongs to XML.
 *
 * @since 12
 */
#define UDMF_META_SMIL "com.real.smil"

/**
 * @brief Markdown.
 * This type belongs to PLAIN_TEXT.
 *
 * @since 12
 */
#define UDMF_META_MARKDOWN "general.markdown"

/**
 * @brief Generic type of the fax.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_FAX "general.fax"

/**
 * @brief J2 jConnect fax file format.
 * This type belongs to FAX.
 *
 * @since 12
 */
#define UDMF_META_JFX_FAX "com.j2.jfx-fax"

/**
 * @brief EFX file format.
 * This type belongs to FAX.
 *
 * @since 12
 */
#define UDMF_META_EFX_FAX "com.js.efx-fax"

/**
 * @brief X BitMAP (XBM) used in the X Window system (X11).
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_XBITMAP_IMAGE "general.xbitmap-image"

/**
 * @brief Tagged Graphics (TGA) format.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_TGA_IMAGE "com.truevision.tga-image"

/**
 * @brief Silicon Graphics image (SGI) format.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_SGI_IMAGE "com.sgi.sgi-image"

/**
 * @brief OpenXR image format.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_OPENEXR_IMAGE "com.ilm.openexr-image"

/**
 * @brief FlashPix image format.
 * This type belongs to IMAGE.
 *
 * @since 12
 */
#define UDMF_META_FLASHPIX_IMAGE "com.kodak.flashpix.image"

/**
 * @brief RealMedia format.
 * This type belongs to VIDEO.
 *
 * @since 12
 */
#define UDMF_META_REALMEDIA "com.real.realmedia"

/**
 * @brief AU format.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_AU_AUDIO "general.au-audio"

/**
 * @brief AIFC.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_AIFC_AUDIO "general.aifc-audio"

/**
 * @brief Digidesign Sound Designer II (SDII).
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_SD2_AUDIO "com.digidesign.sd2-audio"

/**
 * @brief RealAudio.
 * This type belongs to AUDIO.
 *
 * @since 12
 */
#define UDMF_META_REALAUDIO "com.real.realaudio"

/**
 * @brief OpenXML base type.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_OPENXML "org.openxmlformats.openxml"

/**
 * @brief WordProcessingML format.
 * This type belongs to OPENXML and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_WORDPROCESSINGML_DOCUMENT "org.openxmlformats.wordprocessingml.document"

/**
 * @brief SpreadsheetML format.
 * This type belongs to OPENXML and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_SPREADSHEETML_SHEET "org.openxmlformats.spreadsheetml.sheet"

/**
 * @brief PresentationML format.
 * This type belongs to OPENXML and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_PRESENTATIONML_PRESENTATION "org.openxmlformats.presentationml.presentation"

/**
 * @brief OpenDocument format for Office applications.
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT "org.oasis.opendocument"

/**
 * @brief OpenDocument format for word processing (text) documents.
 * This type belongs to OPENDOCUMENT and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_TEXT "org.oasis.opendocument.text"

/**
 * @brief OpenDocument format for spreadsheets.
 * This type belongs to OPENDOCUMENT and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_SPREADSHEET "org.oasis.opendocument.spreadsheet"

/**
 * @brief OpenDocument format for presentations.
 * This type belongs to OPENDOCUMENT and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_PRESENTATION "org.oasis.opendocument.presentation"

/**
 * @brief OpenDocument format for graphics.
 * This type belongs to OPENDOCUMENT and COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_GRAPHICS "org.oasis.opendocument.graphics"

/**
 * @brief OpenDocument format for formula.
 * This type belongs to OPENDOCUMENT.
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_FORMULA "org.oasis.opendocument.formula"

/**
 * @brief Stuffit compression format (stuffit archive).
 * This type belongs to ARCHIVE.
 *
 * @since 12
 */
#define UDMF_META_STUFFIT_ARCHIVE "com.allume.stuffit-archive"

/**
 * @brief VCalendar (VCS) format.
 * This type belongs to CALENDAR and TEXT.
 *
 * @since 12
 */
#define UDMF_META_VCS "general.vcs"

/**
 * @brief Internet Calendaring and Scheduling (ICS) format.
 * This type belongs to CALENDAR and TEXT.
 *
 * @since 12
 */
#define UDMF_META_ICS "general.ics"

/**
 * @brief Generic type of all executable files.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_EXECUTABLE "general.executable"

/**
 * @brief Microsoft Windows portable executable format.
 * This type belongs to EXECUTABLE.
 *
 * @since 12
 */
#define UDMF_META_PORTABLE_EXECUTABLE "com.microsoft.portable-executable"

/**
 * @brief Java class file format.
 * This type belongs to EXECUTABLE.
 *
 * @since 12
 */
#define UDMF_META_SUN_JAVA_CLASS "com.sun.java-class"

/**
 * @brief Basic type of fonts.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_FONT "general.font"

/**
 * @brief TrueType font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_FONT "general.truetype-font"

/**
 * @brief TrueType Collection font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_COLLECTION_FONT "general.truetype-collection-font"

/**
 * @brief OpenType font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_OPENTYPE_FONT "general.opentype-font"

/**
 * @brief PostScript font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_FONT "com.adobe.postscript-font"

/**
 * @brief PostScript Font Binary font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFB_FONT "com.adobe.postscript-pfb-font"

/**
 * @brief Adobe Type 1 font format.
 * This type belongs to FONT.
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFA_FONT "com.adobe.postscript-pfa-font"

/**
 * @brief Memo format defined for the system.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HDOC "openharmony.hdoc"

/**
 * @brief Note format defined for the system.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HINOTE "openharmony.hinote"

/**
 * @brief Style string type defined for the system.
 * This type belongs to COMPOSITE_OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_STYLED_STRING "openharmony.styled-string"

/**
 * @brief Want defined for the system.
 * This type belongs to OBJECT.
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_WANT "openharmony.want"

/**
 * @brief File address type.
 * This type belongs to TEXT.
 *
 * @since 13
 */
#define UDMF_META_GENERAL_FILE_URI "general.file-uri"

/**
 * @brief Content card type.
 * This type belongs to OBJECT.
 *
 * @since 14
 */
#define UDMF_METE_GENERAL_CONTENT_FORM "general.content-form"

#ifdef __cplusplus
};
#endif

/** @} */
#endif