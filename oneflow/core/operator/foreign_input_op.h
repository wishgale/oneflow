#ifndef ONEFLOW_CORE_OPERATOR_FOREIGN_INPUT_OP_H_
#define ONEFLOW_CORE_OPERATOR_FOREIGN_INPUT_OP_H_

#include "oneflow/core/operator/operator.h"

namespace oneflow {

class ForeignInputOp final : public Operator {
 public:
  OF_DISALLOW_COPY_AND_MOVE(ForeignInputOp);
  ForeignInputOp() : Operator() {}
  ~ForeignInputOp() = default;

  void InitFromOpConf() override;
  const PbMessage& GetCustomizedConf() const override;
  void InferBlobDescs(std::function<BlobDesc*(const std::string&)> GetBlobDesc4BnInOp,
                      const ParallelContext* parallel_ctx) const override;

 private:
  void InferHasBatchDim(std::function<bool*(const std::string&)> HasBatchDim4BnInOp) const override;
  void GetSbpSignatures(SbpSignatureList* sbp_sig_list) const override;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_OPERATOR_FOREIGN_INPUT_OP_H_
