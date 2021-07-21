/*
 *  Copyright (c) 2020 NetEase Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*
 * Project: curve
 * Created Date: 2021-8-13
 * Author: chengyi
 */

#include "curvefs/src/metaserver/s3/metaserver_s3.h"

namespace curvefs {
namespace metaserver {
void S3ClientImpl::Init(const curve::common::S3AdapterOption& option) {
    s3Adapter_.Init(option);
}

int S3ClientImpl::Delete(const std::string& name) {
    int ret = 0;
    const Aws::String aws_key(name.c_str(), name.length());
    LOG(INFO) << "delete start, aws_key: " << aws_key;
    if (!s3Adapter_.ObjectExist(aws_key)) {
        // the aws_key is not exist
        LOG(INFO) << "delete object error, aws_key: " << aws_key
                  << " is not exist";
        return 1;
    }
    ret = s3Adapter_.DeleteObject(aws_key);
    if (ret < 0) {
        // -1
        LOG(ERROR) << "delete object: " << aws_key << " get error:" << ret;
    } else {
        // 0
        LOG(INFO) << "delete object: " << aws_key << " end, ret:" << ret;
    }

    return ret;
}
}  // namespace metaserver
}  // namespace curvefs