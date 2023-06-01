;; Auto-generated. Do not edit!


(when (boundp 'motion::eventResult)
  (if (not (find-package "MOTION"))
    (make-package "MOTION"))
  (shadow 'eventResult (find-package "MOTION")))
(unless (find-package "MOTION::EVENTRESULT")
  (make-package "MOTION::EVENTRESULT"))

(in-package "ROS")
;;//! \htmlinclude eventResult.msg.html


(defclass motion::eventResult
  :super ros::object
  :slots (_event_id _result_id ))

(defmethod motion::eventResult
  (:init
   (&key
    ((:event_id __event_id) 0)
    ((:result_id __result_id) 0)
    )
   (send-super :init)
   (setq _event_id (round __event_id))
   (setq _result_id (round __result_id))
   self)
  (:event_id
   (&optional __event_id)
   (if __event_id (setq _event_id __event_id)) _event_id)
  (:result_id
   (&optional __result_id)
   (if __result_id (setq _result_id __result_id)) _result_id)
  (:serialization-length
   ()
   (+
    ;; int32 _event_id
    4
    ;; int32 _result_id
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _event_id
       (write-long _event_id s)
     ;; int32 _result_id
       (write-long _result_id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _event_id
     (setq _event_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _result_id
     (setq _result_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get motion::eventResult :md5sum-) "50b2a692d66763516dc7b791eb0fc50b")
(setf (get motion::eventResult :datatype-) "motion/eventResult")
(setf (get motion::eventResult :definition-)
      "int32 event_id
int32 result_id

")



(provide :motion/eventResult "50b2a692d66763516dc7b791eb0fc50b")


