# 🎮 COS 344 — Computer Graphics

> From mathematical foundations to fully rendered 3D scenes using OpenGL.

---

## 📌 Overview

This repository contains implementations for **COS 344 (Computer Graphics)** practical assignments.

The work follows a structured progression:
- Building **mathematical foundations**
- Rendering **2D scenes**
- Expanding into **3D environments**
- Enhancing realism with **lighting, textures, and translucency**

All rendering is done using **OpenGL 3.3**, with a strong emphasis on understanding the **graphics pipeline from first principles**.

---

## 📂 Practicals

---

### 🧮 Practical 1 — Mathematical Foundations

📄 Spec: :contentReference[oaicite:0]{index=0}  

#### 🧠 Focus
Implement core **linear algebra structures and operations** used in computer graphics.

#### ⚙️ Features
- Vector and Matrix classes
- Linear algebra operations:
  - Vector addition, dot product, cross product
  - Matrix multiplication, transpose, determinant
- Shape abstraction:
  - Triangle and Square representations
- Transformation support using matrices

#### 🎯 Goal
Build the **mathematical backbone** required for rendering systems.

---

### 🎨 Practical 2 — 2D Rendering

📄 Spec: :contentReference[oaicite:1]{index=1}  

#### 🧠 Focus
Render a **2D scene** using OpenGL and apply transformations.

#### 🧩 Scene
A **miniature golf course layout**, including:
- Floor, obstacles, water, ball, and hole
- Multiple shapes (rectangles, triangles, circles)
- Distinct colour mapping for objects

#### ⚙️ Features
- Object selection via keyboard
- Transformations:
  - Translation (WASD)
  - Scaling (+ / -)
  - Rotation (Q / E)
- Wireframe rendering mode (GL_LINES)
- Real-time interaction

#### 🎯 Goal
Understand how objects are **constructed, transformed, and rendered in 2D space**

---

### 🧊 Practical 3 — 3D Rendering

📄 Spec: :contentReference[oaicite:2]{index=2}  

#### 🧠 Focus
Build a **low-polygon 3D scene** with hierarchical transformations.

#### 🧩 Scene
A **mini-golf course with a windmill obstacle**, featuring:
- Course layout with boundaries and decorations
- A rotating windmill with blades
- Real-world inspired modelling

#### ⚙️ Features
- 3D shape construction:
  - Cuboids, cylinders, cones, prisms
- Scene transformations:
  - Rotation (XYZ axes)
  - Translation in 3D space
- Animated components:
  - Rotating windmill blades with controllable speed
- Wireframe toggle

#### 🎯 Goal
Transition from 2D to **interactive 3D rendering and animation**

---

### 💡 Practical 4 — Lighting, Textures & Translucency

📄 Spec: :contentReference[oaicite:3]{index=3}  

#### 🧠 Focus
Enhance realism using **lighting models and texture mapping**

#### 🧩 Scene
A **translucent 3D glass golf ball** with:
- Internal light source
- Light projection onto a surface
- Adjustable geometry detail

#### ⚙️ Features
- Texture mapping:
  - Colour maps
  - Displacement maps (true geometry changes)
  - Alpha maps (transparency)
- Dynamic lighting:
  - Point light source inside object
- Material control:
  - Colour and transparency adjustments
- Runtime controls:
  - Vertex resolution changes
  - Light movement
- Scene transformations and reset functionality

#### 🎯 Goal
Simulate **realistic rendering effects** using lighting and textures

---

## 🛠️ Tech Stack

<p align="center">

<img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Graphics-OpenGL%203.3-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Concepts-Linear%20Algebra-green?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Rendering-2D%20%7C%203D-purple?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Advanced-Lighting%20%7C%20Textures-black?style=for-the-badge"/>

</p>

---

## ⚙️ Implementation Notes

- All implementations:
  - Use **C++ (C++11 standard)** :contentReference[oaicite:4]{index=4}  
  - Use **OpenGL 3.3 only** :contentReference[oaicite:5]{index=5}  
- No external high-level libraries for core logic
- All shapes, textures, and objects are **manually created**
- Focus is on **understanding the pipeline**, not abstraction

---

## 📊 Key Concepts Covered

- Linear algebra in graphics
- Transformation matrices
- Rendering pipelines
- Object modelling (2D & 3D)
- Scene interaction
- Lighting models
- Texture mapping techniques

---

## 🎯 Learning Outcomes

Through these practicals:

- Understand how graphics systems are built **from the ground up**
- Implement **mathematical models for rendering**
- Create **interactive 2D and 3D environments**
- Apply **realistic lighting and texture techniques**
- Gain hands-on experience with **OpenGL rendering**

---

## 🚀 Final Thought

> Computer Graphics is where mathematics meets visual reality —  
> every pixel on the screen is the result of deliberate computation.
