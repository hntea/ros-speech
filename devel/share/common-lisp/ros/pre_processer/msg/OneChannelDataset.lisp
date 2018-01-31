; Auto-generated. Do not edit!


(cl:in-package pre_processer-msg)


;//! \htmlinclude OneChannelDataset.msg.html

(cl:defclass <OneChannelDataset> (roslisp-msg-protocol:ros-message)
  ((size
    :reader size
    :initarg :size
    :type cl:integer
    :initform 0)
   (s_data
    :reader s_data
    :initarg :s_data
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (mfcc
    :reader mfcc
    :initarg :mfcc
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (zero
    :reader zero
    :initarg :zero
    :type cl:float
    :initform 0.0)
   (energy
    :reader energy
    :initarg :energy
    :type cl:float
    :initform 0.0)
   (mfccl2
    :reader mfccl2
    :initarg :mfccl2
    :type cl:float
    :initform 0.0)
   (vad_state
    :reader vad_state
    :initarg :vad_state
    :type cl:integer
    :initform 0))
)

(cl:defclass OneChannelDataset (<OneChannelDataset>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OneChannelDataset>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OneChannelDataset)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pre_processer-msg:<OneChannelDataset> is deprecated: use pre_processer-msg:OneChannelDataset instead.")))

(cl:ensure-generic-function 'size-val :lambda-list '(m))
(cl:defmethod size-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:size-val is deprecated.  Use pre_processer-msg:size instead.")
  (size m))

(cl:ensure-generic-function 's_data-val :lambda-list '(m))
(cl:defmethod s_data-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:s_data-val is deprecated.  Use pre_processer-msg:s_data instead.")
  (s_data m))

(cl:ensure-generic-function 'mfcc-val :lambda-list '(m))
(cl:defmethod mfcc-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:mfcc-val is deprecated.  Use pre_processer-msg:mfcc instead.")
  (mfcc m))

(cl:ensure-generic-function 'zero-val :lambda-list '(m))
(cl:defmethod zero-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:zero-val is deprecated.  Use pre_processer-msg:zero instead.")
  (zero m))

(cl:ensure-generic-function 'energy-val :lambda-list '(m))
(cl:defmethod energy-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:energy-val is deprecated.  Use pre_processer-msg:energy instead.")
  (energy m))

(cl:ensure-generic-function 'mfccl2-val :lambda-list '(m))
(cl:defmethod mfccl2-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:mfccl2-val is deprecated.  Use pre_processer-msg:mfccl2 instead.")
  (mfccl2 m))

(cl:ensure-generic-function 'vad_state-val :lambda-list '(m))
(cl:defmethod vad_state-val ((m <OneChannelDataset>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pre_processer-msg:vad_state-val is deprecated.  Use pre_processer-msg:vad_state instead.")
  (vad_state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OneChannelDataset>) ostream)
  "Serializes a message object of type '<OneChannelDataset>"
  (cl:let* ((signed (cl:slot-value msg 'size)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 's_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 's_data))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'mfcc))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'mfcc))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'zero))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'energy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'mfccl2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'vad_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OneChannelDataset>) istream)
  "Deserializes a message object of type '<OneChannelDataset>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'size) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 's_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 's_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'mfcc) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'mfcc)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zero) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'energy) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'mfccl2) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vad_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OneChannelDataset>)))
  "Returns string type for a message object of type '<OneChannelDataset>"
  "pre_processer/OneChannelDataset")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OneChannelDataset)))
  "Returns string type for a message object of type 'OneChannelDataset"
  "pre_processer/OneChannelDataset")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OneChannelDataset>)))
  "Returns md5sum for a message object of type '<OneChannelDataset>"
  "121cf30206060e130908f4ec26d884b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OneChannelDataset)))
  "Returns md5sum for a message object of type 'OneChannelDataset"
  "121cf30206060e130908f4ec26d884b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OneChannelDataset>)))
  "Returns full string definition for message of type '<OneChannelDataset>"
  (cl:format cl:nil "int32 size~%float64[] s_data~%float64[] mfcc~%float64 zero~%float64 energy~%float64 mfccl2~%int32 vad_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OneChannelDataset)))
  "Returns full string definition for message of type 'OneChannelDataset"
  (cl:format cl:nil "int32 size~%float64[] s_data~%float64[] mfcc~%float64 zero~%float64 energy~%float64 mfccl2~%int32 vad_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OneChannelDataset>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 's_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'mfcc) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     8
     8
     8
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OneChannelDataset>))
  "Converts a ROS message object to a list"
  (cl:list 'OneChannelDataset
    (cl:cons ':size (size msg))
    (cl:cons ':s_data (s_data msg))
    (cl:cons ':mfcc (mfcc msg))
    (cl:cons ':zero (zero msg))
    (cl:cons ':energy (energy msg))
    (cl:cons ':mfccl2 (mfccl2 msg))
    (cl:cons ':vad_state (vad_state msg))
))
