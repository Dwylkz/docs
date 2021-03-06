// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: main.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "main.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace test {

namespace {

const ::google::protobuf::Descriptor* Test_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Test_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_main_2eproto() {
  protobuf_AddDesc_main_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "main.proto");
  GOOGLE_CHECK(file != NULL);
  Test_descriptor_ = file->message_type(0);
  static const int Test_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Test, a_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Test, b_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Test, c_),
  };
  Test_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Test_descriptor_,
      Test::default_instance_,
      Test_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Test, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Test, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Test));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_main_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Test_descriptor_, &Test::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_main_2eproto() {
  delete Test::default_instance_;
  delete Test_reflection_;
}

void protobuf_AddDesc_main_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nmain.proto\022\004test\"\'\n\004Test\022\t\n\001a\030\001 \001(\t\022\t\n"
    "\001b\030\002 \001(\t\022\t\n\001c\030\003 \003(\t", 59);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "main.proto", &protobuf_RegisterTypes);
  Test::default_instance_ = new Test();
  Test::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_main_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_main_2eproto {
  StaticDescriptorInitializer_main_2eproto() {
    protobuf_AddDesc_main_2eproto();
  }
} static_descriptor_initializer_main_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Test::kAFieldNumber;
const int Test::kBFieldNumber;
const int Test::kCFieldNumber;
#endif  // !_MSC_VER

Test::Test()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:test.Test)
}

void Test::InitAsDefaultInstance() {
}

Test::Test(const Test& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:test.Test)
}

void Test::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  a_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  b_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Test::~Test() {
  // @@protoc_insertion_point(destructor:test.Test)
  SharedDtor();
}

void Test::SharedDtor() {
  if (a_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete a_;
  }
  if (b_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete b_;
  }
  if (this != default_instance_) {
  }
}

void Test::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Test::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Test_descriptor_;
}

const Test& Test::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_main_2eproto();
  return *default_instance_;
}

Test* Test::default_instance_ = NULL;

Test* Test::New() const {
  return new Test;
}

void Test::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_a()) {
      if (a_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        a_->clear();
      }
    }
    if (has_b()) {
      if (b_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        b_->clear();
      }
    }
  }
  c_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Test::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:test.Test)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string a = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_a()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->a().data(), this->a().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "a");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_b;
        break;
      }

      // optional string b = 2;
      case 2: {
        if (tag == 18) {
         parse_b:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_b()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->b().data(), this->b().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "b");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_c;
        break;
      }

      // repeated string c = 3;
      case 3: {
        if (tag == 26) {
         parse_c:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_c()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->c(this->c_size() - 1).data(),
            this->c(this->c_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "c");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_c;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:test.Test)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:test.Test)
  return false;
#undef DO_
}

void Test::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:test.Test)
  // optional string a = 1;
  if (has_a()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->a().data(), this->a().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "a");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->a(), output);
  }

  // optional string b = 2;
  if (has_b()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->b().data(), this->b().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "b");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->b(), output);
  }

  // repeated string c = 3;
  for (int i = 0; i < this->c_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
    this->c(i).data(), this->c(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE,
    "c");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->c(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:test.Test)
}

::google::protobuf::uint8* Test::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.Test)
  // optional string a = 1;
  if (has_a()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->a().data(), this->a().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "a");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->a(), target);
  }

  // optional string b = 2;
  if (has_b()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->b().data(), this->b().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "b");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->b(), target);
  }

  // repeated string c = 3;
  for (int i = 0; i < this->c_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->c(i).data(), this->c(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "c");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(3, this->c(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.Test)
  return target;
}

int Test::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string a = 1;
    if (has_a()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->a());
    }

    // optional string b = 2;
    if (has_b()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->b());
    }

  }
  // repeated string c = 3;
  total_size += 1 * this->c_size();
  for (int i = 0; i < this->c_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->c(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Test::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Test* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Test*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Test::MergeFrom(const Test& from) {
  GOOGLE_CHECK_NE(&from, this);
  c_.MergeFrom(from.c_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_a()) {
      set_a(from.a());
    }
    if (from.has_b()) {
      set_b(from.b());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Test::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Test::CopyFrom(const Test& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Test::IsInitialized() const {

  return true;
}

void Test::Swap(Test* other) {
  if (other != this) {
    std::swap(a_, other->a_);
    std::swap(b_, other->b_);
    c_.Swap(&other->c_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Test::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Test_descriptor_;
  metadata.reflection = Test_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace test

// @@protoc_insertion_point(global_scope)
