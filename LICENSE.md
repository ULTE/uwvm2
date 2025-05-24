# **Anti-Sideloading Hosted Platform License v1.0**  
**First Published: May 23, 2025**  
**Copyright © 2025 UlteSoft Open Source Organization**  
**Licensed under the Anti-Sideloading Hosted Platform License v1.0 (ASHP-1.0)**  
**Everyone is permitted to copy and distribute verbatim copies of this license document, but modification is prohibited.**  


## **1. Definitions**  
### 1.1 **"Hosted Platform"** means an execution environment providing:  
    (a) A full operating system supporting standard libraries (e.g., libc implementations) and OS APIs (filesystem, threads, dynamic memory management);  
    (b) Application binary interface (ABI) stability for user-space programs.  

### 1.2 **"Platform Triplet"**  
A machine-readable identifier structured as `<architecture>[-vendor][-system][-extra]`, where:  
- **Architecture** (mandatory): Specifies the CPU instruction set (e.g., `x86_64`, `aarch64`, `riscv64`).  
- **Vendor** (optional): Identifies the platform vendor or maintainer (e.g., `apple`, `microsoft`, `gnu`). Omitted if vendor neutrality is required (denoted as `unknown`).  
- **System** (mandatory): Defines the base operating system or kernel (e.g., `linux`, `darwin`, `windows`).  
- **Extra** (optional): Provides disambiguation for OS variants or critical runtime environments (e.g., `musl`, `android31`, `uefi`).  

#### **Format Rules**:  
- The Triplet must uniquely identify the Hosted Platform's execution environment.  
- Omitted fields shall be replaced with empty segments, but the hierarchical structure must retain at least `<architecture>-system` (e.g., `armv7-linux-android` or `x86_64-unknown-freebsd`).  
- System distributors must document Triplet construction rules in machine-readable manifests.  

#### **Examples**:  
- `x86_64-pc-windows-msvc` (Full specification)  
- `aarch64-apple-darwin` (Omitted `extra`)  
- `riscv64-unknown-linux-openwrt` (Generic vendor)  
- `armv7-linux-android` (Omitted vendor, `android` as `extra`)  

#### **Technical Rationale**  
This extended Triplet format:  
1. **Backward Compatibility**: Maintains compatibility with legacy `<architecture-vendor-system>` conventions (e.g., GNU triplets).  
2. **OS Precision**: The `extra` field allows granular identification of:  
    - Libc implementations (`gnu`, `musl`, `bionic`)  
    - Runtime environments (`win32`, `coreclr`, `nodejs`)  
    - Security contexts (`sel4`, `tee`, `sgx`)  
3. **Vendor Neutrality**: Explicit `unknown` vendor designation prevents ambiguous commercial claims.  

#### **Compliance Implications**  
- A Platform Triplet `armv8-unknown-linux-android` and `armv8-google-linux-android` are considered **distinct** due to differing vendors.  
- Triplets without `extra` (e.g., `x86_64-unknown-linux`) imply the **default** runtime environment for that OS.  

#### **Fork Differentiation**

1. **Fork Differentiation**  
    Derivative OS versions **must** declare distinct `variant` values from their base systems:
    * OpenHarmony: aarch64-linux-ohos (Compliant)  
    * HarmonyNEXT: aarch64-linux-ohos-harmony_next (Violates §3.1) 

2. **Vendor-System Binding**  
    * Darwin (generic): unknown-apple-darwin (Compliant)
    * macOS: unknown-apple-darwin-macos (Compliant)
    * iOS: aarch64-apple-darwin-ios (Violates §3.1) 

3. **Mandatory Requirements:**  
    (a) **Technical Descriptor Obligation**  
        Any modification to the original platform's sideloading policy **must** be reflected through unique technical descriptors in the `variant` field.  

    (b) **Violation Annotation Rules**  
        Platforms violating §3.1 **shall** be identified with **verbatim violation markers** in their triplets:  
        ``` 
        {architecture}-{vendor}-{system}-{violation_type}_{technical_descriptor}  
        ```  

#### **Fork Identification Protocol**  
    Platforms must implement automated variant detection:
    - Hosted Platforms must implement machine-verifiable triplet generation through their native build toolchains.

### 1.3 **"Sideloading"** means installing software outside the Hosted Platform’s curated distribution channels.  

## **2. License Grant**  
### 2.1 **Copyright License**: Subject to Section 3, You are granted a perpetual, worldwide, non-exclusive license to:  
    (a) Use, reproduce, and distribute the Work;  
    (b) Create Derivative Works;  
    (c) Publicly perform/display the Work.  

### 2.2 **Patent License**: Contributors grant You a non-exclusive, royalty-free patent license to make/use/sell the Work.  

## **3. Conditions and Limitations**  
### **3.1 Hosted Platform Compliance**  
Any use of the Work (original or modified) on a Hosted Platform requires:  
    (a) The Platform Triplet must allow **bit-for-bit compatible binaries** to execute via Sideloading;  
    (b) Platform vendors must publish verifiable proofs of compliance through:  
        i. Reproducible build toolchains;  
        ii. Cryptographic attestation of Platform Triplet constraints;  
        iii. Open test suites validating sideloading capabilities.  

### **3.2 Distribution Requirements**  
    (a) All copies must retain copyright/patent/license notices;  
    (b) Derivative Works must state prominent changes from the original;  
    (c) Source distributions must include a `PLATFORM_COMPLIANCE.md` file documenting Sideloading guarantees.  

### **3.3 Platform Enforcement**  
If a Hosted Platform restricts Sideloading for a specific Platform Triplet:  
    (a) All software targeting that Triplet is prohibited from using the Work;  
    (b) Platform vendors must issue public revocation notices;  
    (c) Affected Triplets are blacklisted in the reference compliance registry.  

## **4. Technical Validation**  
### 4.1 **Compliance Proof**: Platform vendors must provide:  
    (a) A formal specification of Platform Triplet generation rules;  
    (b) SBOM (Software Bill of Materials) hashes for all ABI-critical components;  

### 4.2 **Attestation Protocol**: Compliance evidence shall be signed using W3C Verifiable Credentials and published in a decentralized ledger.  

### 4.3 **Application-Layer Security Obligations**  
Any software ("Application") built upon a Hosted Platform using this Work **must** implement technical safeguards to ensure the **secure execution of sideloaded components**.

## **5. Termination**  
Failure to comply with Section 3 automatically terminates all rights. Termination does not affect parties in compliance.  

## **6. Disclaimer**  
**UNLESS REQUIRED BY APPLICABLE LAW, THE WORK IS PROVIDED "AS IS" WITHOUT WARRANTIES. IN NO EVENT SHALL CONTRIBUTORS BE LIABLE FOR DIRECT/INDIRECT DAMAGES.**  

## **7. Jurisdictional Neutrality & Enforcement**  
### **7.1 Sovereign Immunity**  
This License and all rights granted herein are expressly exempt from the jurisdictional control of any national government, state apparatus, or regulatory body, including but not limited to:  
- Legislative frameworks of the United States (e.g., CFIUS regulations, EAR export controls)  
- EU Digital Markets Act platform governance mechanisms  
- National cybersecurity laws requiring backdoor access  

### **7.2 Dispute Resolution Protocol**  
Notwithstanding Section 4.1, violations of this License shall be resolved through binding arbitration under:  
- **United Nations Commission on International Trade Law (UNCITRAL) Rules**  
- **Seat of Arbitration**: Geneva, Switzerland  
- **Enforcement**: Awards shall be enforceable under the New York Convention 1958  

### **7.3 Limited Waiver**  
By exercising rights under this License, all parties consent to:  
    (a) Personal jurisdiction in arbitration proceedings  
    (b) Enforcement of awards through national courts as needed  

---

**SPDX Identifier**: `ASHP-1.0`  
**Compatibility**: Combines Apache-2.0 patent/copyright clauses with platform freedom constraints.  

