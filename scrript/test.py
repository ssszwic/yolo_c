import torch.nn as nn
import torch

# input = torch.ones(1, 1, 4, 4)
# # conv = nn.Conv2d(3, 1, 6, 2, 2, bias=False)
# weight = torch.tensor([[1, 0, 3], [4, 2, 0], [3, 0, 1]], dtype=torch.float32)
# bias = torch.ones(1)
# weight = torch.unsqueeze(weight, dim=0)
# weight = torch.unsqueeze(weight, dim=0)
# # out = conv(input)
# out = torch.nn.functional.conv2d(input, weight, bias=None, stride=[2, 2], padding=[1, 1])
# print(out)


def save_tensor(file_name, t):
    with open(file_name, 'w+') as f:
        while len(t.shape) != 4:
            t = t.unsqueeze(dim=0)
        f.write(f"{t.shape[0]} {t.shape[1]} {t.shape[2]} {t.shape[3]} \n")
        f.write('\n')
        for n in range(t.shape[0]):
            for c in range(t.shape[1]):
                for h in range(t.shape[2]):
                    for w in range(t.shape[3]):
                        f.write(f"{t[n][c][h][w]} ")
                    f.write('\n')
                f.write('\n')
            f.write('\n')
        f.write('\n')


if __name__ == '__main__':
    input = torch.rand(1, 3, 640, 640)
    weight = torch.rand(32, 3, 6, 6)
    bias = torch.rand(32)
    save_tensor('/SSD/szw/Work/yolo_c/resource/bias.txt', bias)
    save_tensor('/SSD/szw/Work/yolo_c/resource/input.txt', input)
    save_tensor('/SSD/szw/Work/yolo_c/resource/weight.txt', weight)
    out = torch.nn.functional.conv2d(input, weight, bias=bias, stride=[2, 2], padding=[2, 2])
    save_tensor('/SSD/szw/Work/yolo_c/resource/out.txt', out)