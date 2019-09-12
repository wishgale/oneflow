#include "oneflow/core/data/weed_deep_dataset.h"
#include "oneflow/core/common/str_util.h"
#include "oneflow/core/persistence/file_system.h"
#include "oneflow/core/persistence/persistent_in_stream.h"
// #include "oneflow/core/record/coco.pb.h"
// #include <opencv2/opencv.hpp>

namespace oneflow {
namespace data {

void WideDeepDataset::Init() {
  CHECK_EQ(dataset_proto().dataset_catalog_case(), DatasetProto::kWideDeep);

}

std::unique_ptr<OFRecord> WideDeepDataset::EncodeOneRecord(int64_t idx) const {
  TODO();
}

DataInstance WideDeepDataset::GetData(int64_t idx, const DataInstanceProto& data_inst_proto) const {
  DataInstance data_inst;
  for (auto pair : data_inst_proto.fields()) {
    data_inst.AddField(pair.first, pair.second);
  }

  PersistentInStream in_stream(
      DataFS(), JoinPath(dataset_proto().dataset_dir(), 
      dataset_proto().wide_deep().data_path()), offset_of_lines_.at(idx));
  std::string line;
  CHECK_EQ_OR_RETURN(in_stream.ReadLine(&line), 0);
  std::vector<std::string> tokens = StrSplit(line, "\t");
  CHECK_GT_OR_RETURN(tokens.size(), 4);
  FOR_RANGE(size_t, i, 4, tokens.size()) {
    tokens = fields[i].split(':')
    assert len(tokens) == 2
    f_id = int(tokens[0])-1
    if f_id in self.feat_to_field:
        f_field = self.feat_to_field[f_id] + start_id
        f_value = float(tokens[1])
        f_mask = 1.0
        feat_cache.append((f_id, f_field, f_value, f_mask))
        if f_field not in field_cache:
            field_cache[f_field] = 1
        else:
            field_cache[f_field] += 1
  }
}

void WideDeepDataset::StatOffsetOfLines() {
  PersistentInStream in_stream(
      DataFS(), JoinPath(dataset_proto().dataset_dir(), 
      dataset_proto().wide_deep().data_path()));
  std::string line;
  size_t bytes = 0;
  while (in_stream.ReadLine(&line) == 0) { 
    offset_of_lines_.push_back(bytes);
    bytes += line.size();
  }
}

void WideDeepDataset::ReadFields() {
  PersistentInStream in_stream(
      DataFS(), JoinPath(dataset_proto().dataset_dir(), 
      dataset_proto().wide_deep().feature_fields_file()));
  int64_t feild_id = 0;
  std::string line;
  while (in_stream.ReadLine(&line) == 0) { 
    Trim(line);
    CHECK_OR_RETURN(feild2field_id_.emplace(line, feild_id).second);
    feild_id += 1;
  }
}

void WideDeepDataset::ReadFeatureIndexList() {
  PersistentInStream in_stream(
      DataFS(), JoinPath(dataset_proto().dataset_dir(), 
      dataset_proto().wide_deep().feature_index_list_file()));
  std::string line;
  while (in_stream.ReadLine(&line) == 0) {
    auto tokens = StrSplit(line, "\t");
    CHECK_EQ_OR_RETURN(tokens.size(), 2);
    auto fields = StrSplit(tokens.at(0), "\a");
    CHECK_GE_OR_RETURN(fields.size(), 1);
    Trim(fields.at(0));
    int64_t feat_id = std::stoi(tokens.at(1));
    if (feat_id + 1 > field_ids_.size()) {
      field_ids_.resize(feat_id + 1, -1);
    }
    field_ids_.at(feat_id) = feild2field_id_.at(fields.at(0));
  }
}

REGISTER_DATASET(DatasetProto::kWideDeep, WideDeepDataset);

}  // namespace data
}  // namespace oneflow
