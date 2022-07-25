; Auto-generated. Do not edit!


(cl:in-package diagnostic_msgs-srv)


;//! \htmlinclude AddDiagnostics-request.msg.html

(cl:defclass <AddDiagnostics-request> (roslisp-msg-protocol:ros-message)
  ((load_namespace
    :reader load_namespace
    :initarg :load_namespace
    :type cl:string
    :initform ""))
)

(cl:defclass AddDiagnostics-request (<AddDiagnostics-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddDiagnostics-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddDiagnostics-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name diagnostic_msgs-srv:<AddDiagnostics-request> is deprecated: use diagnostic_msgs-srv:AddDiagnostics-request instead.")))

(cl:ensure-generic-function 'load_namespace-val :lambda-list '(m))
(cl:defmethod load_namespace-val ((m <AddDiagnostics-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader diagnostic_msgs-srv:load_namespace-val is deprecated.  Use diagnostic_msgs-srv:load_namespace instead.")
  (load_namespace m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddDiagnostics-request>) ostream)
  "Serializes a message object of type '<AddDiagnostics-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'load_namespace))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'load_namespace))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddDiagnostics-request>) istream)
  "Deserializes a message object of type '<AddDiagnostics-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'load_namespace) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'load_namespace) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddDiagnostics-request>)))
  "Returns string type for a service object of type '<AddDiagnostics-request>"
  "diagnostic_msgs/AddDiagnosticsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddDiagnostics-request)))
  "Returns string type for a service object of type 'AddDiagnostics-request"
  "diagnostic_msgs/AddDiagnosticsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddDiagnostics-request>)))
  "Returns md5sum for a message object of type '<AddDiagnostics-request>"
  "e6ac9bbde83d0d3186523c3687aecaee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddDiagnostics-request)))
  "Returns md5sum for a message object of type 'AddDiagnostics-request"
  "e6ac9bbde83d0d3186523c3687aecaee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddDiagnostics-request>)))
  "Returns full string definition for message of type '<AddDiagnostics-request>"
  (cl:format cl:nil "# This service is used as part of the process for loading analyzers at runtime,~%# and should be used by a loader script or program, not as a standalone service.~%# Information about dynamic addition of analyzers can be found at~%# http://wiki.ros.org/diagnostics/Tutorials/Adding%20Analyzers%20at%20Runtime~%~%# The load_namespace parameter defines the namespace where parameters for the~%# initialization of analyzers in the diagnostic aggregator have been loaded. The~%# value should be a global name (i.e. /my/name/space), not a relative~%# (my/name/space) or private (~~my/name/space) name. Analyzers will not be added~%# if a non-global name is used. The call will also fail if the namespace~%# contains parameters that follow a namespace structure that does not conform to~%# that expected by the analyzer definitions. See~%# http://wiki.ros.org/diagnostics/Tutorials/Configuring%20Diagnostic%20Aggregators~%# and http://wiki.ros.org/diagnostics/Tutorials/Using%20the%20GenericAnalyzer~%# for examples of the structure of yaml files which are expected to have been~%# loaded into the namespace.~%string load_namespace~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddDiagnostics-request)))
  "Returns full string definition for message of type 'AddDiagnostics-request"
  (cl:format cl:nil "# This service is used as part of the process for loading analyzers at runtime,~%# and should be used by a loader script or program, not as a standalone service.~%# Information about dynamic addition of analyzers can be found at~%# http://wiki.ros.org/diagnostics/Tutorials/Adding%20Analyzers%20at%20Runtime~%~%# The load_namespace parameter defines the namespace where parameters for the~%# initialization of analyzers in the diagnostic aggregator have been loaded. The~%# value should be a global name (i.e. /my/name/space), not a relative~%# (my/name/space) or private (~~my/name/space) name. Analyzers will not be added~%# if a non-global name is used. The call will also fail if the namespace~%# contains parameters that follow a namespace structure that does not conform to~%# that expected by the analyzer definitions. See~%# http://wiki.ros.org/diagnostics/Tutorials/Configuring%20Diagnostic%20Aggregators~%# and http://wiki.ros.org/diagnostics/Tutorials/Using%20the%20GenericAnalyzer~%# for examples of the structure of yaml files which are expected to have been~%# loaded into the namespace.~%string load_namespace~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddDiagnostics-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'load_namespace))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddDiagnostics-request>))
  "Converts a ROS message object to a list"
  (cl:list 'AddDiagnostics-request
    (cl:cons ':load_namespace (load_namespace msg))
))
;//! \htmlinclude AddDiagnostics-response.msg.html

(cl:defclass <AddDiagnostics-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass AddDiagnostics-response (<AddDiagnostics-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddDiagnostics-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddDiagnostics-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name diagnostic_msgs-srv:<AddDiagnostics-response> is deprecated: use diagnostic_msgs-srv:AddDiagnostics-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <AddDiagnostics-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader diagnostic_msgs-srv:success-val is deprecated.  Use diagnostic_msgs-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <AddDiagnostics-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader diagnostic_msgs-srv:message-val is deprecated.  Use diagnostic_msgs-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddDiagnostics-response>) ostream)
  "Serializes a message object of type '<AddDiagnostics-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddDiagnostics-response>) istream)
  "Deserializes a message object of type '<AddDiagnostics-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddDiagnostics-response>)))
  "Returns string type for a service object of type '<AddDiagnostics-response>"
  "diagnostic_msgs/AddDiagnosticsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddDiagnostics-response)))
  "Returns string type for a service object of type 'AddDiagnostics-response"
  "diagnostic_msgs/AddDiagnosticsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddDiagnostics-response>)))
  "Returns md5sum for a message object of type '<AddDiagnostics-response>"
  "e6ac9bbde83d0d3186523c3687aecaee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddDiagnostics-response)))
  "Returns md5sum for a message object of type 'AddDiagnostics-response"
  "e6ac9bbde83d0d3186523c3687aecaee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddDiagnostics-response>)))
  "Returns full string definition for message of type '<AddDiagnostics-response>"
  (cl:format cl:nil "~%# True if diagnostic aggregator was updated with new diagnostics, False~%# otherwise. A false return value means that either there is a bond in the~%# aggregator which already used the requested namespace, or the initialization~%# of analyzers failed.~%bool success~%~%# Message with additional information about the success or failure~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddDiagnostics-response)))
  "Returns full string definition for message of type 'AddDiagnostics-response"
  (cl:format cl:nil "~%# True if diagnostic aggregator was updated with new diagnostics, False~%# otherwise. A false return value means that either there is a bond in the~%# aggregator which already used the requested namespace, or the initialization~%# of analyzers failed.~%bool success~%~%# Message with additional information about the success or failure~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddDiagnostics-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddDiagnostics-response>))
  "Converts a ROS message object to a list"
  (cl:list 'AddDiagnostics-response
    (cl:cons ':success (success msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'AddDiagnostics)))
  'AddDiagnostics-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'AddDiagnostics)))
  'AddDiagnostics-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddDiagnostics)))
  "Returns string type for a service object of type '<AddDiagnostics>"
  "diagnostic_msgs/AddDiagnostics")