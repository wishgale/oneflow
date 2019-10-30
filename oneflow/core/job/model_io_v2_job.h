#ifndef ONEFLOW_CORE_JOB_MODEL_IO_V2_JOB_
#define ONEFLOW_CORE_JOB_MODEL_IO_V2_JOB_

#include "oneflow/core/job/compiler.h"
#include "oneflow/core/job/inter_user_job_info.pb.h"

namespace oneflow {

void MakeModelIoV2Jobs(const std::vector<Job>& jobs, const HashMap<std::string, ParallelBlobConf>&,
                       const std::function<void(Job*)>& Handler);

}  // namespace oneflow

#endif  // ONEFLOW_CORE_JOB_MODEL_IO_V2_JOB_
