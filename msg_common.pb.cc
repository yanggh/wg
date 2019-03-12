// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_common.proto

#include "msg_common.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace mpfmessage {
class MsgCommonDataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<MsgCommonData>
      _instance;
} _MsgCommonData_default_instance_;
}  // namespace mpfmessage
namespace protobuf_msg_5fcommon_2eproto {
void InitDefaultsMsgCommonDataImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::mpfmessage::_MsgCommonData_default_instance_;
    new (ptr) ::mpfmessage::MsgCommonData();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mpfmessage::MsgCommonData::InitAsDefaultInstance();
}

void InitDefaultsMsgCommonData() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsMsgCommonDataImpl);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[5];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::mpfmessage::MsgCommonData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::mpfmessage::MsgCommonData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::mpfmessage::MsgCommonData, code_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::mpfmessage::MsgCommonData, descriprion_),
  1,
  0,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::mpfmessage::MsgCommonData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::mpfmessage::_MsgCommonData_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "msg_common.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\020msg_common.proto\022\nmpfmessage\"2\n\rMsgCom"
      "monData\022\014\n\004code\030\001 \001(\r\022\023\n\013descriprion\030\002 \001"
      "(\t*I\n\nResultCode\022\013\n\007SUCCESS\020\001\022\010\n\004FAIL\020\002\022"
      "\022\n\016UNKNOWN_RESULT\020\003\022\020\n\014OTHER_RESULT\020\004*l\n"
      "\025MESSAGE_CMD_CODE_BASE\022\030\n\022RA_MODUAL_CMD_"
      "BASE\020\204\216\006\022\032\n\024SNMP_MODUAL_CMD_BASE\020\350\216\006\022\035\n\027"
      "NETFLOW_MODUAL_CMD_BASE\020\314\217\006*\373\003\n\025SNMP_MES"
      "SAGE_CMD_CODE\022\020\n\014SNMP_GET_MSG\020\001\022\021\n\rSNMP_"
      "RESP_MSG\020\002\022\026\n\022SNMP_SEND_TRAP_MSG\020\003\022\032\n\026TO"
      "PO_DISCOVERY_REQ_MSG\020\004\022\035\n\031TOPO_DISCOVERY"
      "_NOTIFY_MSG\020\005\022\024\n\020RES_SYNC_REQ_MSG\020\006\022\027\n\023R"
      "ES_SYNC_NOTIFY_MSG\020\007\022\034\n\030DEV_PERF_COLLECT"
      "_REQ_MSG\020\010\022\036\n\032GET_HOST_PROC_LIST_REQ_MSG"
      "\020\t\022\033\n\027DB_PERF_COLLECT_REQ_MSG\020\n\022 \n\034MIDWA"
      "RE_PERF_COLLECT_REQ_MSG\020\013\022\031\n\025ROOM_RES_SY"
      "NC_REQ_MSG\020\014\022\034\n\030GET_SENSER_VALUE_REQ_MSG"
      "\020\r\022%\n!GET_HOST_FILE_SYSTEM_LIST_REQ_MSG\020"
      "\016\022\035\n\031CONNECTIVITY_TEST_REQ_MSG\020\017\022\035\n\031REAC"
      "HABILITY_TEST_REQ_MSG\020\020\022 \n\034REACHABILITY_"
      "TEST_NOTIFY_MSG\020\021*\213\001\n\017ERROR_CODE_BASE\022\026\n"
      "\022ERROR_CODE_SUCCESS\020\000\022\034\n\026COMMON_ERROR_CO"
      "DE_BASE\020\300\232\014\022\037\n\031RA_MODUAL_ERROR_CODE_BASE"
      "\020\244\233\014\022!\n\033SNMP_MODUAL_ERROR_CODE_BASE\020\210\234\014*"
      ")\n\017SNMP_ERROR_CODE\022\026\n\022SNMP_CONNECT_ERROR"
      "\020\001B\002H\001"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 966);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "msg_common.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_msg_5fcommon_2eproto
namespace mpfmessage {
const ::google::protobuf::EnumDescriptor* ResultCode_descriptor() {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_msg_5fcommon_2eproto::file_level_enum_descriptors[0];
}
bool ResultCode_IsValid(int value) {
  switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* MESSAGE_CMD_CODE_BASE_descriptor() {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_msg_5fcommon_2eproto::file_level_enum_descriptors[1];
}
bool MESSAGE_CMD_CODE_BASE_IsValid(int value) {
  switch (value) {
    case 100100:
    case 100200:
    case 100300:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* SNMP_MESSAGE_CMD_CODE_descriptor() {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_msg_5fcommon_2eproto::file_level_enum_descriptors[2];
}
bool SNMP_MESSAGE_CMD_CODE_IsValid(int value) {
  switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ERROR_CODE_BASE_descriptor() {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_msg_5fcommon_2eproto::file_level_enum_descriptors[3];
}
bool ERROR_CODE_BASE_IsValid(int value) {
  switch (value) {
    case 0:
    case 200000:
    case 200100:
    case 200200:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* SNMP_ERROR_CODE_descriptor() {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_msg_5fcommon_2eproto::file_level_enum_descriptors[4];
}
bool SNMP_ERROR_CODE_IsValid(int value) {
  switch (value) {
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void MsgCommonData::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MsgCommonData::kCodeFieldNumber;
const int MsgCommonData::kDescriprionFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MsgCommonData::MsgCommonData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_msg_5fcommon_2eproto::InitDefaultsMsgCommonData();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:mpfmessage.MsgCommonData)
}
MsgCommonData::MsgCommonData(const MsgCommonData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  descriprion_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_descriprion()) {
    descriprion_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.descriprion_);
  }
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:mpfmessage.MsgCommonData)
}

void MsgCommonData::SharedCtor() {
  _cached_size_ = 0;
  descriprion_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  code_ = 0u;
}

MsgCommonData::~MsgCommonData() {
  // @@protoc_insertion_point(destructor:mpfmessage.MsgCommonData)
  SharedDtor();
}

void MsgCommonData::SharedDtor() {
  descriprion_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void MsgCommonData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MsgCommonData::descriptor() {
  ::protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_msg_5fcommon_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const MsgCommonData& MsgCommonData::default_instance() {
  ::protobuf_msg_5fcommon_2eproto::InitDefaultsMsgCommonData();
  return *internal_default_instance();
}

MsgCommonData* MsgCommonData::New(::google::protobuf::Arena* arena) const {
  MsgCommonData* n = new MsgCommonData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MsgCommonData::Clear() {
// @@protoc_insertion_point(message_clear_start:mpfmessage.MsgCommonData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(!descriprion_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
    (*descriprion_.UnsafeRawStringPointer())->clear();
  }
  code_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool MsgCommonData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:mpfmessage.MsgCommonData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 code = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_code();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &code_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string descriprion = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_descriprion()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->descriprion().data(), static_cast<int>(this->descriprion().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "mpfmessage.MsgCommonData.descriprion");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:mpfmessage.MsgCommonData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:mpfmessage.MsgCommonData)
  return false;
#undef DO_
}

void MsgCommonData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:mpfmessage.MsgCommonData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 code = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->code(), output);
  }

  // optional string descriprion = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->descriprion().data(), static_cast<int>(this->descriprion().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "mpfmessage.MsgCommonData.descriprion");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->descriprion(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:mpfmessage.MsgCommonData)
}

::google::protobuf::uint8* MsgCommonData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:mpfmessage.MsgCommonData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 code = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->code(), target);
  }

  // optional string descriprion = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->descriprion().data(), static_cast<int>(this->descriprion().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "mpfmessage.MsgCommonData.descriprion");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->descriprion(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mpfmessage.MsgCommonData)
  return target;
}

size_t MsgCommonData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mpfmessage.MsgCommonData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (_has_bits_[0 / 32] & 3u) {
    // optional string descriprion = 2;
    if (has_descriprion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->descriprion());
    }

    // optional uint32 code = 1;
    if (has_code()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->code());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MsgCommonData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mpfmessage.MsgCommonData)
  GOOGLE_DCHECK_NE(&from, this);
  const MsgCommonData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const MsgCommonData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mpfmessage.MsgCommonData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mpfmessage.MsgCommonData)
    MergeFrom(*source);
  }
}

void MsgCommonData::MergeFrom(const MsgCommonData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mpfmessage.MsgCommonData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 3u) {
    if (cached_has_bits & 0x00000001u) {
      set_has_descriprion();
      descriprion_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.descriprion_);
    }
    if (cached_has_bits & 0x00000002u) {
      code_ = from.code_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void MsgCommonData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mpfmessage.MsgCommonData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MsgCommonData::CopyFrom(const MsgCommonData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mpfmessage.MsgCommonData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgCommonData::IsInitialized() const {
  return true;
}

void MsgCommonData::Swap(MsgCommonData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MsgCommonData::InternalSwap(MsgCommonData* other) {
  using std::swap;
  descriprion_.Swap(&other->descriprion_);
  swap(code_, other->code_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MsgCommonData::GetMetadata() const {
  protobuf_msg_5fcommon_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_msg_5fcommon_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace mpfmessage

// @@protoc_insertion_point(global_scope)
