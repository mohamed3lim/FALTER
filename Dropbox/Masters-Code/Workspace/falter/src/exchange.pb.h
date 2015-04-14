// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: exchange.proto

#ifndef PROTOBUF_exchange_2eproto__INCLUDED
#define PROTOBUF_exchange_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_exchange_2eproto();
void protobuf_AssignDesc_exchange_2eproto();
void protobuf_ShutdownFile_exchange_2eproto();

class Image;
class SrfData;
class Data;

// ===================================================================

class Image : public ::google::protobuf::Message {
 public:
  Image();
  virtual ~Image();

  Image(const Image& from);

  inline Image& operator=(const Image& from) {
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
  static const Image& default_instance();

  void Swap(Image* other);

  // implements Message ----------------------------------------------

  Image* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Image& from);
  void MergeFrom(const Image& from);
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

  // repeated float input_pmd = 1;
  inline int input_pmd_size() const;
  inline void clear_input_pmd();
  static const int kInputPmdFieldNumber = 1;
  inline float input_pmd(int index) const;
  inline void set_input_pmd(int index, float value);
  inline void add_input_pmd(float value);
  inline const ::google::protobuf::RepeatedField< float >&
      input_pmd() const;
  inline ::google::protobuf::RepeatedField< float >*
      mutable_input_pmd();

  // @@protoc_insertion_point(class_scope:Image)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedField< float > input_pmd_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static Image* default_instance_;
};
// -------------------------------------------------------------------

class SrfData : public ::google::protobuf::Message {
 public:
  SrfData();
  virtual ~SrfData();

  SrfData(const SrfData& from);

  inline SrfData& operator=(const SrfData& from) {
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
  static const SrfData& default_instance();

  void Swap(SrfData* other);

  // implements Message ----------------------------------------------

  SrfData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SrfData& from);
  void MergeFrom(const SrfData& from);
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

  // optional double srf_gnd = 1;
  inline bool has_srf_gnd() const;
  inline void clear_srf_gnd();
  static const int kSrfGndFieldNumber = 1;
  inline double srf_gnd() const;
  inline void set_srf_gnd(double value);

  // optional double srf_rhs = 2;
  inline bool has_srf_rhs() const;
  inline void clear_srf_rhs();
  static const int kSrfRhsFieldNumber = 2;
  inline double srf_rhs() const;
  inline void set_srf_rhs(double value);

  // optional double srf_lhs = 3;
  inline bool has_srf_lhs() const;
  inline void clear_srf_lhs();
  static const int kSrfLhsFieldNumber = 3;
  inline double srf_lhs() const;
  inline void set_srf_lhs(double value);

  // optional double srf_front_rhs = 4;
  inline bool has_srf_front_rhs() const;
  inline void clear_srf_front_rhs();
  static const int kSrfFrontRhsFieldNumber = 4;
  inline double srf_front_rhs() const;
  inline void set_srf_front_rhs(double value);

  // optional double srf_front_ctr = 5;
  inline bool has_srf_front_ctr() const;
  inline void clear_srf_front_ctr();
  static const int kSrfFrontCtrFieldNumber = 5;
  inline double srf_front_ctr() const;
  inline void set_srf_front_ctr(double value);

  // optional double srf_front_lhs = 6;
  inline bool has_srf_front_lhs() const;
  inline void clear_srf_front_lhs();
  static const int kSrfFrontLhsFieldNumber = 6;
  inline double srf_front_lhs() const;
  inline void set_srf_front_lhs(double value);

  // optional double srf_rear = 7;
  inline bool has_srf_rear() const;
  inline void clear_srf_rear();
  static const int kSrfRearFieldNumber = 7;
  inline double srf_rear() const;
  inline void set_srf_rear(double value);

  // optional double srf_ceiling = 8;
  inline bool has_srf_ceiling() const;
  inline void clear_srf_ceiling();
  static const int kSrfCeilingFieldNumber = 8;
  inline double srf_ceiling() const;
  inline void set_srf_ceiling(double value);

  // @@protoc_insertion_point(class_scope:SrfData)
 private:
  inline void set_has_srf_gnd();
  inline void clear_has_srf_gnd();
  inline void set_has_srf_rhs();
  inline void clear_has_srf_rhs();
  inline void set_has_srf_lhs();
  inline void clear_has_srf_lhs();
  inline void set_has_srf_front_rhs();
  inline void clear_has_srf_front_rhs();
  inline void set_has_srf_front_ctr();
  inline void clear_has_srf_front_ctr();
  inline void set_has_srf_front_lhs();
  inline void clear_has_srf_front_lhs();
  inline void set_has_srf_rear();
  inline void clear_has_srf_rear();
  inline void set_has_srf_ceiling();
  inline void clear_has_srf_ceiling();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double srf_gnd_;
  double srf_rhs_;
  double srf_lhs_;
  double srf_front_rhs_;
  double srf_front_ctr_;
  double srf_front_lhs_;
  double srf_rear_;
  double srf_ceiling_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static SrfData* default_instance_;
};
// -------------------------------------------------------------------

class Data : public ::google::protobuf::Message {
 public:
  Data();
  virtual ~Data();

  Data(const Data& from);

  inline Data& operator=(const Data& from) {
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
  static const Data& default_instance();

  void Swap(Data* other);

  // implements Message ----------------------------------------------

  Data* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Data& from);
  void MergeFrom(const Data& from);
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

  // repeated .Image image = 1;
  inline int image_size() const;
  inline void clear_image();
  static const int kImageFieldNumber = 1;
  inline const ::Image& image(int index) const;
  inline ::Image* mutable_image(int index);
  inline ::Image* add_image();
  inline const ::google::protobuf::RepeatedPtrField< ::Image >&
      image() const;
  inline ::google::protobuf::RepeatedPtrField< ::Image >*
      mutable_image();

  // repeated .SrfData srfData = 2;
  inline int srfdata_size() const;
  inline void clear_srfdata();
  static const int kSrfDataFieldNumber = 2;
  inline const ::SrfData& srfdata(int index) const;
  inline ::SrfData* mutable_srfdata(int index);
  inline ::SrfData* add_srfdata();
  inline const ::google::protobuf::RepeatedPtrField< ::SrfData >&
      srfdata() const;
  inline ::google::protobuf::RepeatedPtrField< ::SrfData >*
      mutable_srfdata();

  // optional double xPos = 3;
  inline bool has_xpos() const;
  inline void clear_xpos();
  static const int kXPosFieldNumber = 3;
  inline double xpos() const;
  inline void set_xpos(double value);

  // optional double yPos = 4;
  inline bool has_ypos() const;
  inline void clear_ypos();
  static const int kYPosFieldNumber = 4;
  inline double ypos() const;
  inline void set_ypos(double value);

  // optional double zPos = 5;
  inline bool has_zpos() const;
  inline void clear_zpos();
  static const int kZPosFieldNumber = 5;
  inline double zpos() const;
  inline void set_zpos(double value);

  // optional double currAngle = 6;
  inline bool has_currangle() const;
  inline void clear_currangle();
  static const int kCurrAngleFieldNumber = 6;
  inline double currangle() const;
  inline void set_currangle(double value);

  // @@protoc_insertion_point(class_scope:Data)
 private:
  inline void set_has_xpos();
  inline void clear_has_xpos();
  inline void set_has_ypos();
  inline void clear_has_ypos();
  inline void set_has_zpos();
  inline void clear_has_zpos();
  inline void set_has_currangle();
  inline void clear_has_currangle();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Image > image_;
  ::google::protobuf::RepeatedPtrField< ::SrfData > srfdata_;
  double xpos_;
  double ypos_;
  double zpos_;
  double currangle_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static Data* default_instance_;
};
// ===================================================================


// ===================================================================

// Image

// repeated float input_pmd = 1;
inline int Image::input_pmd_size() const {
  return input_pmd_.size();
}
inline void Image::clear_input_pmd() {
  input_pmd_.Clear();
}
inline float Image::input_pmd(int index) const {
  return input_pmd_.Get(index);
}
inline void Image::set_input_pmd(int index, float value) {
  input_pmd_.Set(index, value);
}
inline void Image::add_input_pmd(float value) {
  input_pmd_.Add(value);
}
inline const ::google::protobuf::RepeatedField< float >&
Image::input_pmd() const {
  return input_pmd_;
}
inline ::google::protobuf::RepeatedField< float >*
Image::mutable_input_pmd() {
  return &input_pmd_;
}

// -------------------------------------------------------------------

// SrfData

// optional double srf_gnd = 1;
inline bool SrfData::has_srf_gnd() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SrfData::set_has_srf_gnd() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SrfData::clear_has_srf_gnd() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SrfData::clear_srf_gnd() {
  srf_gnd_ = 0;
  clear_has_srf_gnd();
}
inline double SrfData::srf_gnd() const {
  return srf_gnd_;
}
inline void SrfData::set_srf_gnd(double value) {
  set_has_srf_gnd();
  srf_gnd_ = value;
}

// optional double srf_rhs = 2;
inline bool SrfData::has_srf_rhs() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SrfData::set_has_srf_rhs() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SrfData::clear_has_srf_rhs() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SrfData::clear_srf_rhs() {
  srf_rhs_ = 0;
  clear_has_srf_rhs();
}
inline double SrfData::srf_rhs() const {
  return srf_rhs_;
}
inline void SrfData::set_srf_rhs(double value) {
  set_has_srf_rhs();
  srf_rhs_ = value;
}

// optional double srf_lhs = 3;
inline bool SrfData::has_srf_lhs() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SrfData::set_has_srf_lhs() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SrfData::clear_has_srf_lhs() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SrfData::clear_srf_lhs() {
  srf_lhs_ = 0;
  clear_has_srf_lhs();
}
inline double SrfData::srf_lhs() const {
  return srf_lhs_;
}
inline void SrfData::set_srf_lhs(double value) {
  set_has_srf_lhs();
  srf_lhs_ = value;
}

// optional double srf_front_rhs = 4;
inline bool SrfData::has_srf_front_rhs() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SrfData::set_has_srf_front_rhs() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SrfData::clear_has_srf_front_rhs() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SrfData::clear_srf_front_rhs() {
  srf_front_rhs_ = 0;
  clear_has_srf_front_rhs();
}
inline double SrfData::srf_front_rhs() const {
  return srf_front_rhs_;
}
inline void SrfData::set_srf_front_rhs(double value) {
  set_has_srf_front_rhs();
  srf_front_rhs_ = value;
}

// optional double srf_front_ctr = 5;
inline bool SrfData::has_srf_front_ctr() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SrfData::set_has_srf_front_ctr() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SrfData::clear_has_srf_front_ctr() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SrfData::clear_srf_front_ctr() {
  srf_front_ctr_ = 0;
  clear_has_srf_front_ctr();
}
inline double SrfData::srf_front_ctr() const {
  return srf_front_ctr_;
}
inline void SrfData::set_srf_front_ctr(double value) {
  set_has_srf_front_ctr();
  srf_front_ctr_ = value;
}

// optional double srf_front_lhs = 6;
inline bool SrfData::has_srf_front_lhs() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void SrfData::set_has_srf_front_lhs() {
  _has_bits_[0] |= 0x00000020u;
}
inline void SrfData::clear_has_srf_front_lhs() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void SrfData::clear_srf_front_lhs() {
  srf_front_lhs_ = 0;
  clear_has_srf_front_lhs();
}
inline double SrfData::srf_front_lhs() const {
  return srf_front_lhs_;
}
inline void SrfData::set_srf_front_lhs(double value) {
  set_has_srf_front_lhs();
  srf_front_lhs_ = value;
}

// optional double srf_rear = 7;
inline bool SrfData::has_srf_rear() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void SrfData::set_has_srf_rear() {
  _has_bits_[0] |= 0x00000040u;
}
inline void SrfData::clear_has_srf_rear() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void SrfData::clear_srf_rear() {
  srf_rear_ = 0;
  clear_has_srf_rear();
}
inline double SrfData::srf_rear() const {
  return srf_rear_;
}
inline void SrfData::set_srf_rear(double value) {
  set_has_srf_rear();
  srf_rear_ = value;
}

// optional double srf_ceiling = 8;
inline bool SrfData::has_srf_ceiling() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void SrfData::set_has_srf_ceiling() {
  _has_bits_[0] |= 0x00000080u;
}
inline void SrfData::clear_has_srf_ceiling() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void SrfData::clear_srf_ceiling() {
  srf_ceiling_ = 0;
  clear_has_srf_ceiling();
}
inline double SrfData::srf_ceiling() const {
  return srf_ceiling_;
}
inline void SrfData::set_srf_ceiling(double value) {
  set_has_srf_ceiling();
  srf_ceiling_ = value;
}

// -------------------------------------------------------------------

// Data

// repeated .Image image = 1;
inline int Data::image_size() const {
  return image_.size();
}
inline void Data::clear_image() {
  image_.Clear();
}
inline const ::Image& Data::image(int index) const {
  return image_.Get(index);
}
inline ::Image* Data::mutable_image(int index) {
  return image_.Mutable(index);
}
inline ::Image* Data::add_image() {
  return image_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Image >&
Data::image() const {
  return image_;
}
inline ::google::protobuf::RepeatedPtrField< ::Image >*
Data::mutable_image() {
  return &image_;
}

// repeated .SrfData srfData = 2;
inline int Data::srfdata_size() const {
  return srfdata_.size();
}
inline void Data::clear_srfdata() {
  srfdata_.Clear();
}
inline const ::SrfData& Data::srfdata(int index) const {
  return srfdata_.Get(index);
}
inline ::SrfData* Data::mutable_srfdata(int index) {
  return srfdata_.Mutable(index);
}
inline ::SrfData* Data::add_srfdata() {
  return srfdata_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SrfData >&
Data::srfdata() const {
  return srfdata_;
}
inline ::google::protobuf::RepeatedPtrField< ::SrfData >*
Data::mutable_srfdata() {
  return &srfdata_;
}

// optional double xPos = 3;
inline bool Data::has_xpos() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Data::set_has_xpos() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Data::clear_has_xpos() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Data::clear_xpos() {
  xpos_ = 0;
  clear_has_xpos();
}
inline double Data::xpos() const {
  return xpos_;
}
inline void Data::set_xpos(double value) {
  set_has_xpos();
  xpos_ = value;
}

// optional double yPos = 4;
inline bool Data::has_ypos() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Data::set_has_ypos() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Data::clear_has_ypos() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Data::clear_ypos() {
  ypos_ = 0;
  clear_has_ypos();
}
inline double Data::ypos() const {
  return ypos_;
}
inline void Data::set_ypos(double value) {
  set_has_ypos();
  ypos_ = value;
}

// optional double zPos = 5;
inline bool Data::has_zpos() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Data::set_has_zpos() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Data::clear_has_zpos() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Data::clear_zpos() {
  zpos_ = 0;
  clear_has_zpos();
}
inline double Data::zpos() const {
  return zpos_;
}
inline void Data::set_zpos(double value) {
  set_has_zpos();
  zpos_ = value;
}

// optional double currAngle = 6;
inline bool Data::has_currangle() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Data::set_has_currangle() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Data::clear_has_currangle() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Data::clear_currangle() {
  currangle_ = 0;
  clear_has_currangle();
}
inline double Data::currangle() const {
  return currangle_;
}
inline void Data::set_currangle(double value) {
  set_has_currangle();
  currangle_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_exchange_2eproto__INCLUDED
