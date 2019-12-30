rm log -rf
export CUDA_VISIBLE_DEVICES=1,2,3
python train_batch.py --total_batch_num=10 --base_lr=0.1 --gpu_num_per_node=1 --batch_size=2 --data_part_num=1 --gt_max_len=90 --raw_data=1 --num_of_batches_in_snapshot=10 --shuffle=0 --model_load_dir=../yolov/of_model/yolov3_model_python/
