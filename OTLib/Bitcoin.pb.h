// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Bitcoin.proto

#ifndef PROTOBUF_Bitcoin_2eproto__INCLUDED
#define PROTOBUF_Bitcoin_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace OTDB {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Bitcoin_2eproto();
void protobuf_AssignDesc_Bitcoin_2eproto();
void protobuf_ShutdownFile_Bitcoin_2eproto();

class BitcoinAcct_InternalPB;
class BitcoinServer_InternalPB;

// ===================================================================

class BitcoinAcct_InternalPB : public ::google::protobuf::Message {
 public:
  BitcoinAcct_InternalPB();
  virtual ~BitcoinAcct_InternalPB();
  
  BitcoinAcct_InternalPB(const BitcoinAcct_InternalPB& from);
  
  inline BitcoinAcct_InternalPB& operator=(const BitcoinAcct_InternalPB& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const BitcoinAcct_InternalPB& default_instance();
  
  void Swap(BitcoinAcct_InternalPB* other);
  
  // implements Message ----------------------------------------------
  
  BitcoinAcct_InternalPB* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BitcoinAcct_InternalPB& from);
  void MergeFrom(const BitcoinAcct_InternalPB& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string gui_label = 1;
  inline bool has_gui_label() const;
  inline void clear_gui_label();
  static const int kGuiLabelFieldNumber = 1;
  inline const ::std::string& gui_label() const;
  inline void set_gui_label(const ::std::string& value);
  inline void set_gui_label(const char* value);
  inline void set_gui_label(const char* value, size_t size);
  inline ::std::string* mutable_gui_label();
  inline ::std::string* release_gui_label();
  
  // optional string server_id = 2;
  inline bool has_server_id() const;
  inline void clear_server_id();
  static const int kServerIdFieldNumber = 2;
  inline const ::std::string& server_id() const;
  inline void set_server_id(const ::std::string& value);
  inline void set_server_id(const char* value);
  inline void set_server_id(const char* value, size_t size);
  inline ::std::string* mutable_server_id();
  inline ::std::string* release_server_id();
  
  // optional string acct_id = 3;
  inline bool has_acct_id() const;
  inline void clear_acct_id();
  static const int kAcctIdFieldNumber = 3;
  inline const ::std::string& acct_id() const;
  inline void set_acct_id(const ::std::string& value);
  inline void set_acct_id(const char* value);
  inline void set_acct_id(const char* value, size_t size);
  inline ::std::string* mutable_acct_id();
  inline ::std::string* release_acct_id();
  
  // optional string bitcoin_acct_name = 4;
  inline bool has_bitcoin_acct_name() const;
  inline void clear_bitcoin_acct_name();
  static const int kBitcoinAcctNameFieldNumber = 4;
  inline const ::std::string& bitcoin_acct_name() const;
  inline void set_bitcoin_acct_name(const ::std::string& value);
  inline void set_bitcoin_acct_name(const char* value);
  inline void set_bitcoin_acct_name(const char* value, size_t size);
  inline ::std::string* mutable_bitcoin_acct_name();
  inline ::std::string* release_bitcoin_acct_name();
  
  // @@protoc_insertion_point(class_scope:OTDB.BitcoinAcct_InternalPB)
 private:
  inline void set_has_gui_label();
  inline void clear_has_gui_label();
  inline void set_has_server_id();
  inline void clear_has_server_id();
  inline void set_has_acct_id();
  inline void clear_has_acct_id();
  inline void set_has_bitcoin_acct_name();
  inline void clear_has_bitcoin_acct_name();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* gui_label_;
  ::std::string* server_id_;
  ::std::string* acct_id_;
  ::std::string* bitcoin_acct_name_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_Bitcoin_2eproto();
  friend void protobuf_AssignDesc_Bitcoin_2eproto();
  friend void protobuf_ShutdownFile_Bitcoin_2eproto();
  
  void InitAsDefaultInstance();
  static BitcoinAcct_InternalPB* default_instance_;
};
// -------------------------------------------------------------------

class BitcoinServer_InternalPB : public ::google::protobuf::Message {
 public:
  BitcoinServer_InternalPB();
  virtual ~BitcoinServer_InternalPB();
  
  BitcoinServer_InternalPB(const BitcoinServer_InternalPB& from);
  
  inline BitcoinServer_InternalPB& operator=(const BitcoinServer_InternalPB& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const BitcoinServer_InternalPB& default_instance();
  
  void Swap(BitcoinServer_InternalPB* other);
  
  // implements Message ----------------------------------------------
  
  BitcoinServer_InternalPB* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BitcoinServer_InternalPB& from);
  void MergeFrom(const BitcoinServer_InternalPB& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string gui_label = 1;
  inline bool has_gui_label() const;
  inline void clear_gui_label();
  static const int kGuiLabelFieldNumber = 1;
  inline const ::std::string& gui_label() const;
  inline void set_gui_label(const ::std::string& value);
  inline void set_gui_label(const char* value);
  inline void set_gui_label(const char* value, size_t size);
  inline ::std::string* mutable_gui_label();
  inline ::std::string* release_gui_label();
  
  // optional string server_id = 2;
  inline bool has_server_id() const;
  inline void clear_server_id();
  static const int kServerIdFieldNumber = 2;
  inline const ::std::string& server_id() const;
  inline void set_server_id(const ::std::string& value);
  inline void set_server_id(const char* value);
  inline void set_server_id(const char* value, size_t size);
  inline ::std::string* mutable_server_id();
  inline ::std::string* release_server_id();
  
  // optional string server_type = 3;
  inline bool has_server_type() const;
  inline void clear_server_type();
  static const int kServerTypeFieldNumber = 3;
  inline const ::std::string& server_type() const;
  inline void set_server_type(const ::std::string& value);
  inline void set_server_type(const char* value);
  inline void set_server_type(const char* value, size_t size);
  inline ::std::string* mutable_server_type();
  inline ::std::string* release_server_type();
  
  // optional string server_host = 4;
  inline bool has_server_host() const;
  inline void clear_server_host();
  static const int kServerHostFieldNumber = 4;
  inline const ::std::string& server_host() const;
  inline void set_server_host(const ::std::string& value);
  inline void set_server_host(const char* value);
  inline void set_server_host(const char* value, size_t size);
  inline ::std::string* mutable_server_host();
  inline ::std::string* release_server_host();
  
  // optional string server_port = 5;
  inline bool has_server_port() const;
  inline void clear_server_port();
  static const int kServerPortFieldNumber = 5;
  inline const ::std::string& server_port() const;
  inline void set_server_port(const ::std::string& value);
  inline void set_server_port(const char* value);
  inline void set_server_port(const char* value, size_t size);
  inline ::std::string* mutable_server_port();
  inline ::std::string* release_server_port();
  
  // optional string bitcoin_username = 6;
  inline bool has_bitcoin_username() const;
  inline void clear_bitcoin_username();
  static const int kBitcoinUsernameFieldNumber = 6;
  inline const ::std::string& bitcoin_username() const;
  inline void set_bitcoin_username(const ::std::string& value);
  inline void set_bitcoin_username(const char* value);
  inline void set_bitcoin_username(const char* value, size_t size);
  inline ::std::string* mutable_bitcoin_username();
  inline ::std::string* release_bitcoin_username();
  
  // optional string bitcoin_password = 7;
  inline bool has_bitcoin_password() const;
  inline void clear_bitcoin_password();
  static const int kBitcoinPasswordFieldNumber = 7;
  inline const ::std::string& bitcoin_password() const;
  inline void set_bitcoin_password(const ::std::string& value);
  inline void set_bitcoin_password(const char* value);
  inline void set_bitcoin_password(const char* value, size_t size);
  inline ::std::string* mutable_bitcoin_password();
  inline ::std::string* release_bitcoin_password();
  
  // @@protoc_insertion_point(class_scope:OTDB.BitcoinServer_InternalPB)
 private:
  inline void set_has_gui_label();
  inline void clear_has_gui_label();
  inline void set_has_server_id();
  inline void clear_has_server_id();
  inline void set_has_server_type();
  inline void clear_has_server_type();
  inline void set_has_server_host();
  inline void clear_has_server_host();
  inline void set_has_server_port();
  inline void clear_has_server_port();
  inline void set_has_bitcoin_username();
  inline void clear_has_bitcoin_username();
  inline void set_has_bitcoin_password();
  inline void clear_has_bitcoin_password();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* gui_label_;
  ::std::string* server_id_;
  ::std::string* server_type_;
  ::std::string* server_host_;
  ::std::string* server_port_;
  ::std::string* bitcoin_username_;
  ::std::string* bitcoin_password_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  friend void  protobuf_AddDesc_Bitcoin_2eproto();
  friend void protobuf_AssignDesc_Bitcoin_2eproto();
  friend void protobuf_ShutdownFile_Bitcoin_2eproto();
  
  void InitAsDefaultInstance();
  static BitcoinServer_InternalPB* default_instance_;
};
// ===================================================================


// ===================================================================

// BitcoinAcct_InternalPB

// optional string gui_label = 1;
inline bool BitcoinAcct_InternalPB::has_gui_label() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BitcoinAcct_InternalPB::set_has_gui_label() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BitcoinAcct_InternalPB::clear_has_gui_label() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BitcoinAcct_InternalPB::clear_gui_label() {
  if (gui_label_ != &::google::protobuf::internal::kEmptyString) {
    gui_label_->clear();
  }
  clear_has_gui_label();
}
inline const ::std::string& BitcoinAcct_InternalPB::gui_label() const {
  return *gui_label_;
}
inline void BitcoinAcct_InternalPB::set_gui_label(const ::std::string& value) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_gui_label(const char* value) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_gui_label(const char* value, size_t size) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinAcct_InternalPB::mutable_gui_label() {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  return gui_label_;
}
inline ::std::string* BitcoinAcct_InternalPB::release_gui_label() {
  clear_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = gui_label_;
    gui_label_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string server_id = 2;
inline bool BitcoinAcct_InternalPB::has_server_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BitcoinAcct_InternalPB::set_has_server_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BitcoinAcct_InternalPB::clear_has_server_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BitcoinAcct_InternalPB::clear_server_id() {
  if (server_id_ != &::google::protobuf::internal::kEmptyString) {
    server_id_->clear();
  }
  clear_has_server_id();
}
inline const ::std::string& BitcoinAcct_InternalPB::server_id() const {
  return *server_id_;
}
inline void BitcoinAcct_InternalPB::set_server_id(const ::std::string& value) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_server_id(const char* value) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_server_id(const char* value, size_t size) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinAcct_InternalPB::mutable_server_id() {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  return server_id_;
}
inline ::std::string* BitcoinAcct_InternalPB::release_server_id() {
  clear_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = server_id_;
    server_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string acct_id = 3;
inline bool BitcoinAcct_InternalPB::has_acct_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BitcoinAcct_InternalPB::set_has_acct_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BitcoinAcct_InternalPB::clear_has_acct_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BitcoinAcct_InternalPB::clear_acct_id() {
  if (acct_id_ != &::google::protobuf::internal::kEmptyString) {
    acct_id_->clear();
  }
  clear_has_acct_id();
}
inline const ::std::string& BitcoinAcct_InternalPB::acct_id() const {
  return *acct_id_;
}
inline void BitcoinAcct_InternalPB::set_acct_id(const ::std::string& value) {
  set_has_acct_id();
  if (acct_id_ == &::google::protobuf::internal::kEmptyString) {
    acct_id_ = new ::std::string;
  }
  acct_id_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_acct_id(const char* value) {
  set_has_acct_id();
  if (acct_id_ == &::google::protobuf::internal::kEmptyString) {
    acct_id_ = new ::std::string;
  }
  acct_id_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_acct_id(const char* value, size_t size) {
  set_has_acct_id();
  if (acct_id_ == &::google::protobuf::internal::kEmptyString) {
    acct_id_ = new ::std::string;
  }
  acct_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinAcct_InternalPB::mutable_acct_id() {
  set_has_acct_id();
  if (acct_id_ == &::google::protobuf::internal::kEmptyString) {
    acct_id_ = new ::std::string;
  }
  return acct_id_;
}
inline ::std::string* BitcoinAcct_InternalPB::release_acct_id() {
  clear_has_acct_id();
  if (acct_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = acct_id_;
    acct_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string bitcoin_acct_name = 4;
inline bool BitcoinAcct_InternalPB::has_bitcoin_acct_name() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BitcoinAcct_InternalPB::set_has_bitcoin_acct_name() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BitcoinAcct_InternalPB::clear_has_bitcoin_acct_name() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BitcoinAcct_InternalPB::clear_bitcoin_acct_name() {
  if (bitcoin_acct_name_ != &::google::protobuf::internal::kEmptyString) {
    bitcoin_acct_name_->clear();
  }
  clear_has_bitcoin_acct_name();
}
inline const ::std::string& BitcoinAcct_InternalPB::bitcoin_acct_name() const {
  return *bitcoin_acct_name_;
}
inline void BitcoinAcct_InternalPB::set_bitcoin_acct_name(const ::std::string& value) {
  set_has_bitcoin_acct_name();
  if (bitcoin_acct_name_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_acct_name_ = new ::std::string;
  }
  bitcoin_acct_name_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_bitcoin_acct_name(const char* value) {
  set_has_bitcoin_acct_name();
  if (bitcoin_acct_name_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_acct_name_ = new ::std::string;
  }
  bitcoin_acct_name_->assign(value);
}
inline void BitcoinAcct_InternalPB::set_bitcoin_acct_name(const char* value, size_t size) {
  set_has_bitcoin_acct_name();
  if (bitcoin_acct_name_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_acct_name_ = new ::std::string;
  }
  bitcoin_acct_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinAcct_InternalPB::mutable_bitcoin_acct_name() {
  set_has_bitcoin_acct_name();
  if (bitcoin_acct_name_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_acct_name_ = new ::std::string;
  }
  return bitcoin_acct_name_;
}
inline ::std::string* BitcoinAcct_InternalPB::release_bitcoin_acct_name() {
  clear_has_bitcoin_acct_name();
  if (bitcoin_acct_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = bitcoin_acct_name_;
    bitcoin_acct_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// BitcoinServer_InternalPB

// optional string gui_label = 1;
inline bool BitcoinServer_InternalPB::has_gui_label() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_gui_label() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BitcoinServer_InternalPB::clear_has_gui_label() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BitcoinServer_InternalPB::clear_gui_label() {
  if (gui_label_ != &::google::protobuf::internal::kEmptyString) {
    gui_label_->clear();
  }
  clear_has_gui_label();
}
inline const ::std::string& BitcoinServer_InternalPB::gui_label() const {
  return *gui_label_;
}
inline void BitcoinServer_InternalPB::set_gui_label(const ::std::string& value) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(value);
}
inline void BitcoinServer_InternalPB::set_gui_label(const char* value) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(value);
}
inline void BitcoinServer_InternalPB::set_gui_label(const char* value, size_t size) {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  gui_label_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_gui_label() {
  set_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    gui_label_ = new ::std::string;
  }
  return gui_label_;
}
inline ::std::string* BitcoinServer_InternalPB::release_gui_label() {
  clear_has_gui_label();
  if (gui_label_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = gui_label_;
    gui_label_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string server_id = 2;
inline bool BitcoinServer_InternalPB::has_server_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_server_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BitcoinServer_InternalPB::clear_has_server_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BitcoinServer_InternalPB::clear_server_id() {
  if (server_id_ != &::google::protobuf::internal::kEmptyString) {
    server_id_->clear();
  }
  clear_has_server_id();
}
inline const ::std::string& BitcoinServer_InternalPB::server_id() const {
  return *server_id_;
}
inline void BitcoinServer_InternalPB::set_server_id(const ::std::string& value) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_id(const char* value) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_id(const char* value, size_t size) {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  server_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_server_id() {
  set_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    server_id_ = new ::std::string;
  }
  return server_id_;
}
inline ::std::string* BitcoinServer_InternalPB::release_server_id() {
  clear_has_server_id();
  if (server_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = server_id_;
    server_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string server_type = 3;
inline bool BitcoinServer_InternalPB::has_server_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_server_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BitcoinServer_InternalPB::clear_has_server_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BitcoinServer_InternalPB::clear_server_type() {
  if (server_type_ != &::google::protobuf::internal::kEmptyString) {
    server_type_->clear();
  }
  clear_has_server_type();
}
inline const ::std::string& BitcoinServer_InternalPB::server_type() const {
  return *server_type_;
}
inline void BitcoinServer_InternalPB::set_server_type(const ::std::string& value) {
  set_has_server_type();
  if (server_type_ == &::google::protobuf::internal::kEmptyString) {
    server_type_ = new ::std::string;
  }
  server_type_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_type(const char* value) {
  set_has_server_type();
  if (server_type_ == &::google::protobuf::internal::kEmptyString) {
    server_type_ = new ::std::string;
  }
  server_type_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_type(const char* value, size_t size) {
  set_has_server_type();
  if (server_type_ == &::google::protobuf::internal::kEmptyString) {
    server_type_ = new ::std::string;
  }
  server_type_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_server_type() {
  set_has_server_type();
  if (server_type_ == &::google::protobuf::internal::kEmptyString) {
    server_type_ = new ::std::string;
  }
  return server_type_;
}
inline ::std::string* BitcoinServer_InternalPB::release_server_type() {
  clear_has_server_type();
  if (server_type_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = server_type_;
    server_type_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string server_host = 4;
inline bool BitcoinServer_InternalPB::has_server_host() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_server_host() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BitcoinServer_InternalPB::clear_has_server_host() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BitcoinServer_InternalPB::clear_server_host() {
  if (server_host_ != &::google::protobuf::internal::kEmptyString) {
    server_host_->clear();
  }
  clear_has_server_host();
}
inline const ::std::string& BitcoinServer_InternalPB::server_host() const {
  return *server_host_;
}
inline void BitcoinServer_InternalPB::set_server_host(const ::std::string& value) {
  set_has_server_host();
  if (server_host_ == &::google::protobuf::internal::kEmptyString) {
    server_host_ = new ::std::string;
  }
  server_host_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_host(const char* value) {
  set_has_server_host();
  if (server_host_ == &::google::protobuf::internal::kEmptyString) {
    server_host_ = new ::std::string;
  }
  server_host_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_host(const char* value, size_t size) {
  set_has_server_host();
  if (server_host_ == &::google::protobuf::internal::kEmptyString) {
    server_host_ = new ::std::string;
  }
  server_host_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_server_host() {
  set_has_server_host();
  if (server_host_ == &::google::protobuf::internal::kEmptyString) {
    server_host_ = new ::std::string;
  }
  return server_host_;
}
inline ::std::string* BitcoinServer_InternalPB::release_server_host() {
  clear_has_server_host();
  if (server_host_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = server_host_;
    server_host_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string server_port = 5;
inline bool BitcoinServer_InternalPB::has_server_port() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_server_port() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BitcoinServer_InternalPB::clear_has_server_port() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BitcoinServer_InternalPB::clear_server_port() {
  if (server_port_ != &::google::protobuf::internal::kEmptyString) {
    server_port_->clear();
  }
  clear_has_server_port();
}
inline const ::std::string& BitcoinServer_InternalPB::server_port() const {
  return *server_port_;
}
inline void BitcoinServer_InternalPB::set_server_port(const ::std::string& value) {
  set_has_server_port();
  if (server_port_ == &::google::protobuf::internal::kEmptyString) {
    server_port_ = new ::std::string;
  }
  server_port_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_port(const char* value) {
  set_has_server_port();
  if (server_port_ == &::google::protobuf::internal::kEmptyString) {
    server_port_ = new ::std::string;
  }
  server_port_->assign(value);
}
inline void BitcoinServer_InternalPB::set_server_port(const char* value, size_t size) {
  set_has_server_port();
  if (server_port_ == &::google::protobuf::internal::kEmptyString) {
    server_port_ = new ::std::string;
  }
  server_port_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_server_port() {
  set_has_server_port();
  if (server_port_ == &::google::protobuf::internal::kEmptyString) {
    server_port_ = new ::std::string;
  }
  return server_port_;
}
inline ::std::string* BitcoinServer_InternalPB::release_server_port() {
  clear_has_server_port();
  if (server_port_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = server_port_;
    server_port_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string bitcoin_username = 6;
inline bool BitcoinServer_InternalPB::has_bitcoin_username() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_bitcoin_username() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BitcoinServer_InternalPB::clear_has_bitcoin_username() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BitcoinServer_InternalPB::clear_bitcoin_username() {
  if (bitcoin_username_ != &::google::protobuf::internal::kEmptyString) {
    bitcoin_username_->clear();
  }
  clear_has_bitcoin_username();
}
inline const ::std::string& BitcoinServer_InternalPB::bitcoin_username() const {
  return *bitcoin_username_;
}
inline void BitcoinServer_InternalPB::set_bitcoin_username(const ::std::string& value) {
  set_has_bitcoin_username();
  if (bitcoin_username_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_username_ = new ::std::string;
  }
  bitcoin_username_->assign(value);
}
inline void BitcoinServer_InternalPB::set_bitcoin_username(const char* value) {
  set_has_bitcoin_username();
  if (bitcoin_username_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_username_ = new ::std::string;
  }
  bitcoin_username_->assign(value);
}
inline void BitcoinServer_InternalPB::set_bitcoin_username(const char* value, size_t size) {
  set_has_bitcoin_username();
  if (bitcoin_username_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_username_ = new ::std::string;
  }
  bitcoin_username_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_bitcoin_username() {
  set_has_bitcoin_username();
  if (bitcoin_username_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_username_ = new ::std::string;
  }
  return bitcoin_username_;
}
inline ::std::string* BitcoinServer_InternalPB::release_bitcoin_username() {
  clear_has_bitcoin_username();
  if (bitcoin_username_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = bitcoin_username_;
    bitcoin_username_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string bitcoin_password = 7;
inline bool BitcoinServer_InternalPB::has_bitcoin_password() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void BitcoinServer_InternalPB::set_has_bitcoin_password() {
  _has_bits_[0] |= 0x00000040u;
}
inline void BitcoinServer_InternalPB::clear_has_bitcoin_password() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void BitcoinServer_InternalPB::clear_bitcoin_password() {
  if (bitcoin_password_ != &::google::protobuf::internal::kEmptyString) {
    bitcoin_password_->clear();
  }
  clear_has_bitcoin_password();
}
inline const ::std::string& BitcoinServer_InternalPB::bitcoin_password() const {
  return *bitcoin_password_;
}
inline void BitcoinServer_InternalPB::set_bitcoin_password(const ::std::string& value) {
  set_has_bitcoin_password();
  if (bitcoin_password_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_password_ = new ::std::string;
  }
  bitcoin_password_->assign(value);
}
inline void BitcoinServer_InternalPB::set_bitcoin_password(const char* value) {
  set_has_bitcoin_password();
  if (bitcoin_password_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_password_ = new ::std::string;
  }
  bitcoin_password_->assign(value);
}
inline void BitcoinServer_InternalPB::set_bitcoin_password(const char* value, size_t size) {
  set_has_bitcoin_password();
  if (bitcoin_password_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_password_ = new ::std::string;
  }
  bitcoin_password_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BitcoinServer_InternalPB::mutable_bitcoin_password() {
  set_has_bitcoin_password();
  if (bitcoin_password_ == &::google::protobuf::internal::kEmptyString) {
    bitcoin_password_ = new ::std::string;
  }
  return bitcoin_password_;
}
inline ::std::string* BitcoinServer_InternalPB::release_bitcoin_password() {
  clear_has_bitcoin_password();
  if (bitcoin_password_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = bitcoin_password_;
    bitcoin_password_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace OTDB

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Bitcoin_2eproto__INCLUDED