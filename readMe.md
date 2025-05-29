[TOC]

#  func1, 计算延时

```c++
QElapsedTimer timer;
timer.start();
timer.elapsed()
```

![image-20250529113054377](readMe.assets/image-20250529113054377.png)

#  func2, 正则

QRegularExpression

```c++
QRegularExpression regex;
regex.setPattern(filter);
QRegularExpressionMatch match = regex.match(line.trimmed());
if (match.hasMatch()) {
    matched_lines << line;
}
```



![image-20250529112906581](readMe.assets/image-20250529112906581.png)

